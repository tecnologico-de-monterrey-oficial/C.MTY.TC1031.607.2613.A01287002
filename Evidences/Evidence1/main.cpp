#include "lib/hashFunctions.h"
#include <iostream>

int main() {
    struct DayTime dt = {2024, 2, 29, 14, 30, 45};
    uint32_t date_int = dateToInt(dt);
    std::cout << "Date: " << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hour << ":" << dt.minute << ":" << dt.second << std::endl;
    std::cout << "Integer representation: " << date_int << std::endl;
    struct DayTime dt2 = IntToDate(date_int);
    std::cout << "Converted back: " << dt2.year << "-" << dt2.month << "-" << dt2.day << " " << dt2.hour << ":" << dt2.minute << ":" << dt2.second << std::endl;
    std::cout << std::endl;
    
    struct IPAdress ip = {192, 168, 1, 1};
    uint32_t ip_int = ipToInt(ip);
    std::cout << "IP Address: " << ip.a << "." << ip.b << "." << ip.c << "." << ip.d << std::endl;
    std::cout << "Integer representation: " << ip_int << std::endl;
    struct IPAdress ip2 = intToIp(ip_int);
    std::cout << "Converted back: " << ip2.a << "." << ip2.b << "." << ip2.c << "." << ip2.d << std::endl;
    return 0;
}