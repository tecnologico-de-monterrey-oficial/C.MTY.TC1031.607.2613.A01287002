/**
 * @file hashFunctions.h
 * @brief Hash Functions for IPV4 & DateTime Encoding/Decoding with SEC-DED 
 * Error Correction. 
 * 
 * This header file provides functions to convert between IP addresses and their
 * integer representations, as well as functions to encode and decode IP addresses
 * with SEC-DED error correction. It also includes functions to convert between
 * date/time structures and their integer representations.
 * 
 * Refs: cppreference. (2026). _Fixed width integer types (since C++11)_. 
 *   https://en.cppreference.com/cpp/types/integer
 * Chen, L. (2008). _Hsiao-Code Check Matrices and Recursively Balanced 
 *   Matrices_. https://arxiv.org/abs/0803.1217
 */

#pragma once
#include <cstdint>
#include <stdint.h>

#define prettyPrintStatus(status) \
    (status == ERROR_NONE ? "No Error" : \
    (status == ERROR_CORRECTED_DATA ? "Corrected Data Error" : \
    (status == ERROR_CORRECTED_PARITY ? "Corrected Parity Error" : "Double Error Detected")))

#define printIPAddress(ip) \
    +ip.a << "." << +ip.b << "." << +ip.c << "." << +ip.d

#define printDayTime(dt) \
    +dt.year << "-" << +dt.month << "-" << +dt.day << " " << +dt.hour << ":" << +dt.minute << ":" << +dt.second

typedef enum { ERROR_NONE, ERROR_CORRECTED_DATA, ERROR_CORRECTED_PARITY, ERROR_DOUBLE } Status;

// --- Common SEC-DED Utilities ---

static inline int getHammingWeight(uint8_t val) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_popcount(val);
#else
    int count = 0;
    while (val) {
        count += (val & 1);
        val >>= 1;
    }
    return count;
#endif
}

/**
 * @section IP Address
 * @brief Structures and functions for handling IPv4 addresses with & without 
 * SEC-DED error correction.
 */

typedef struct {
    uint_least8_t a;
    uint_least8_t b; 
    uint_least8_t c;
    uint_least8_t d;
} IPAddress;

typedef struct __attribute__((packed)) {
    IPAddress ip;
    uint_least8_t sec_ded;
} IPAddressSEC_DED;

// Look on attachments/parityMatrixGen.py for the generation of the P_MATRIX [R26]
static const uint8_t IPV4_P_MATRIX[32] = {
    0x07, 0x0B, 0x0D, 0x0E, 0x13, 0x15, 0x16, 0x19,
    0x1A, 0x1C, 0x23, 0x25, 0x26, 0x29, 0x2A, 0x2C,
    0x31, 0x32, 0x34, 0x38, 0x43, 0x45, 0x46, 0x49,
    0x4A, 0x4C, 0x51, 0x52, 0x54, 0x58, 0x61, 0x62
};

static inline uint32_t ipToInt(IPAddress ip) {
    return ((uint32_t)ip.a << 24) | ((uint32_t)ip.b << 16) | 
           ((uint32_t)ip.c << 8)  | (uint32_t)ip.d;
}

static inline IPAddress intToIp(uint32_t ip_int) {
    IPAddress ip;
    ip.a = (ip_int >> 24) & 0xFF;
    ip.b = (ip_int >> 16) & 0xFF;
    ip.c = (ip_int >> 8)  & 0xFF;
    ip.d = ip_int & 0xFF;
    return ip;
}

static inline uint8_t computeIPParity(IPAddress ip) {
    uint32_t val = ipToInt(ip);
    uint8_t parity = 0;
    for (int i = 0; i < 32; i++) {
        if ((val >> i) & 1) parity ^= IPV4_P_MATRIX[i];
    }
    return parity;
}

// --- SEC-DED version of IPV4 ---
void intToIpSEC_DED(IPAddressSEC_DED *packet) {
    packet->sec_ded = computeIPParity(packet->ip);
}

Status verifyAndCorrect(IPAddressSEC_DED *packet) {
    uint8_t calculated_parity = computeIPParity(packet->ip);
    uint8_t syndrome = (calculated_parity ^ packet->sec_ded) & 0x7F;

    if (syndrome == 0) return ERROR_NONE;

    int weight = getHammingWeight(syndrome);

    if (weight == 3) {
        for (int i = 0; i < 32; i++) {
            if (syndrome == IPV4_P_MATRIX[i]) {
                uint32_t val = ipToInt(packet->ip) ^ (1U << i);
                packet->ip = intToIp(val);
                return ERROR_CORRECTED_DATA;
            }
        }
    }

    if (weight == 1) {
        packet->sec_ded ^= syndrome;
        return ERROR_CORRECTED_PARITY;
    }

    return ERROR_DOUBLE;
}

// --- Date ---
// SEC-DED included because of struct size 
typedef struct {
    uint_least16_t year;
    uint_least8_t month;
    uint_least8_t day;
    uint_least8_t hour;
    uint_least8_t minute;
    uint_least8_t second;
    uint_least8_t sec_ded;
} DayTime;

// Look on attachments/parityMatrixGen.py for the generation of the P_MATRIX [R30]
static const uint8_t DATE_P_MATRIX[56] = {
    0x07, 0x0B, 0x0D, 0x0E, 0x13, 0x15, 0x16, 0x19,
    0x1A, 0x1C, 0x23, 0x25, 0x26, 0x29, 0x2A, 0x2C,
    0x31, 0x32, 0x34, 0x38, 0x43, 0x45, 0x46, 0x49,
    0x4A, 0x4C, 0x51, 0x52, 0x54, 0x58, 0x61, 0x62,
    0x64, 0x68, 0x70, 0x83, 0x85, 0x86, 0x89, 0x8A,
    0x8C, 0x91, 0x92, 0x94, 0x98, 0xA1, 0xA2, 0xA4,
    0xA8, 0xB0, 0xC1, 0xC2, 0xC4, 0xC8, 0xD0, 0xE0
};

// --- Bit Serialization Helpers ---
// Packs 56 data bits across year..second into a 64-bit integer bitfield
static inline uint64_t daytimeToU64(const DayTime *dt) {
    return ((uint64_t)(dt->year & 0xFFFF)   << 40) |
           ((uint64_t)(dt->month & 0xFF)    << 32) |
           ((uint64_t)(dt->day & 0xFF)      << 24) |
           ((uint64_t)(dt->hour & 0xFF)     << 16) |
           ((uint64_t)(dt->minute & 0xFF)   << 8)  |
            (uint64_t)(dt->second & 0xFF);
}

// Unpacks 64-bit integer bitfield back into individual DayTime fields
static inline void u64ToDayTime(uint64_t val, DayTime *dt) {
    dt->year   = (val >> 40) & 0xFFFF;
    dt->month  = (val >> 32) & 0xFF;
    dt->day    = (val >> 24) & 0xFF;
    dt->hour   = (val >> 16) & 0xFF;
    dt->minute = (val >> 8)  & 0xFF;
    dt->second =  val        & 0xFF;
}

// --- SEC-DED Implementation ---
// Computes parity byte using XOR over active bit positions in DATE_P_MATRIX
uint8_t computeDayTimeParity(const DayTime *dt) {
    uint64_t data = daytimeToU64(dt);
    uint8_t parity = 0;
    for (int i = 0; i < 56; i++) {
        if ((data >> i) & 1ULL) {
            parity ^= DATE_P_MATRIX[i];
        }
    }
    return parity;
}

// Calculates parity and assigns it to dt->sec_ded
void encodeDayTime(DayTime *dt) {
    dt->sec_ded = computeDayTimeParity(dt);
}

Status verifyAndCorrectDayTime(DayTime *dt) {
    uint8_t calculated_parity = computeDayTimeParity(dt);
    uint8_t syndrome = calculated_parity ^ dt->sec_ded;

    if (syndrome == 0) {
        return ERROR_NONE;
    }

    int weight = getHammingWeight(syndrome);

    if (weight == 3) {
        for (int i = 0; i < 56; i++) {
            if (DATE_P_MATRIX[i] == syndrome) {
                uint64_t data = daytimeToU64(dt);
                data ^= (1ULL << i);
                u64ToDayTime(data, dt);
                return ERROR_CORRECTED_DATA;
            }
        }
    }

    if (weight == 1) {
        dt->sec_ded ^= syndrome;
        return ERROR_CORRECTED_PARITY;
    }

    return ERROR_DOUBLE;
}

// --- User Date Conversion Logic ---
// Returns standard cumulative days since March 1st for a given month index (offset by 3)
static inline int daysSinceMarch(int month) {
    return (month * 367) / 12;
}

uint64_t dateToInt(const DayTime dt) {
    uint_least16_t y = dt.year;
    uint_least8_t m = dt.month;

    // Shift calendar so March is month 0, and Jan/Feb belong to the previous year
    if (m <= 2) {
        m += 12;
        y -= 1;
    }

    uint_least32_t totalDays = (365 * y) + (y / 4) - (y / 100) + (y / 400) + daysSinceMarch(m) + dt.day - 306;

    constexpr uint_least64_t DAYS_AT_EPOCH_2000 = 730485; 
    uint_least32_t daysSince2000 = totalDays - DAYS_AT_EPOCH_2000;
    uint_least64_t totalSeconds = (daysSince2000 * 86400) + 
                                (dt.hour * 3600) + 
                                (dt.minute * 60) + 
                                dt.second;

    return totalSeconds;
}

// Safely converts struct to total seconds, repairing bit flips prior to conversion
bool safeDateToInt(const DayTime *dt, uint64_t *out_seconds) {
    Status status = verifyAndCorrectDayTime((DayTime *)dt);
    if (status == ERROR_DOUBLE) {
        return false; // Fatal double-bit corruption
    }
    *out_seconds = dateToInt(*dt);
    return true;
}