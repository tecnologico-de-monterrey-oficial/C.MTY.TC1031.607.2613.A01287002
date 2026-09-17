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

typedef enum { ERROR_NONE, ERROR_CORRECTED_DATA, ERROR_CORRECTED_PARITY, ERROR_DOUBLE } Status;

// Look on attachments/parityMatrixGen.py for the generation of the P_MATRIX
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

// --- SEC-DED version of IPV4 ---
void intToIpSEC_DED(IPAddressSEC_DED *packet) {
    uint32_t val = ipToInt(packet->ip);
    uint8_t parity = 0;
    for (int i = 0; i < 32; i++) {
        if ((val >> i) & 1) parity ^= IPV4_P_MATRIX[i];
    }
    packet->sec_ded = parity;
}

Status verifyAndCorrect(IPAddressSEC_DED *packet) {
    uint32_t val = ipToInt(packet->ip);
    uint8_t calc_parity = 0;
    for (int i = 0; i < 32; i++) {
        if ((val >> i) & 1) calc_parity ^= IPV4_P_MATRIX[i];
    }

    uint8_t syndrome = (calc_parity ^ packet->sec_ded) & 0x7F;
    if (syndrome == 0) return ERROR_NONE;

    for (int i = 0; i < 32; i++) {
        if (syndrome == IPV4_P_MATRIX[i]) {
            val ^= (1U << i); // Correct corrupted bit
            packet->ip.a = (val >> 24) & 0xFF;
            packet->ip.b = (val >> 16) & 0xFF;
            packet->ip.c = (val >> 8)  & 0xFF;
            packet->ip.d = val & 0xFF;
            return ERROR_CORRECTED_DATA;
        }
    }

    // Single-bit parity error (Weight 1)
    if (__builtin_popcount(syndrome) == 1) {
        packet->sec_ded ^= syndrome;
        return ERROR_CORRECTED_PARITY;
    }
    return ERROR_DOUBLE;
}

// --- Date ---
// TO:DO  : Remove impossible times
// TO:DO 2: Optimize best for 56 bits + 8 for SEC-DED
struct DayTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

auto leapYear = [](int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
};

// Days on each month
auto daysInMonth = [](int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return leapYear(year) ? 29 : 28;
        default:
            return 0; // Invalid month
    }
};

uint32_t dateToInt(struct DayTime dt) {
    if (dt.year < 2000 || dt.year > 2063 || dt.month < 1 || dt.month > 12 ||
        dt.day < 1 || dt.day > daysInMonth(dt.month, dt.year) ||
        dt.hour < 0 || dt.hour > 23 || dt.minute < 0 || dt.minute > 59 ||
        dt.second < 0 || dt.second > 59) {
        return 0; // Invalid date/time
    }

    return ((uint32_t)(dt.year - 2000) << 22) |
           ((uint32_t)(dt.month - 1)   << 18) |
           ((uint32_t)dt.day           << 13) |
           ((uint32_t)dt.hour          << 8)  |
           ((uint32_t)dt.minute        << 2)  |
           ((uint32_t)(dt.second / 15));
}

struct DayTime IntToDate(uint32_t date_int) {
    struct DayTime dt;
    dt.year   = ((date_int >> 22) & 0x3F) + 2000;
    dt.month  = ((date_int >> 18) & 0x0F) + 1;
    dt.day    = (date_int >> 13)  & 0x1F;
    dt.hour   = (date_int >> 8)   & 0x1F;
    dt.minute = (date_int >> 2)   & 0x3F;
    dt.second = (date_int & 0x03) * 0x0F;
    return dt;
}