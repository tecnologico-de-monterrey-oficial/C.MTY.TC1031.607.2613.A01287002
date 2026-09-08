#pragma once
#include <stdint.h>

struct IPAdress {
    int a;
    int b; 
    int c;
    int d;
};

struct DayTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

// --- IP ---

uint32_t ipToInt(struct IPAdress ip) {
    return ((uint32_t)ip.a << 24) |
           ((uint32_t)ip.b << 16) |
           ((uint32_t)ip.c << 8)  |
           ((uint32_t)ip.d);
}

struct IPAdress intToIp(uint32_t ip_int) {
    struct IPAdress ip;
    ip.a = (ip_int >> 24) & 0xFF;
    ip.b = (ip_int >> 16) & 0xFF;
    ip.c = (ip_int >> 8)  & 0xFF;
    ip.d = ip_int & 0xFF;
    return ip;
}

// --- Date ---
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