#include "lib/hashFunctions.h"
#include <iostream>

int main() {
    // struct DayTime dt = {2024, 2, 29, 14, 30, 45};
    // uint32_t date_int = dateToInt(dt);
    // std::cout << "Date: " << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hour << ":" << dt.minute << ":" << dt.second << std::endl;
    // std::cout << "Integer representation: " << date_int << std::endl;
    // struct DayTime dt2 = IntToDate(date_int);
    // std::cout << "Converted back: " << dt2.year << "-" << dt2.month << "-" << dt2.day << " " << dt2.hour << ":" << dt2.minute << ":" << dt2.second << std::endl;
    // std::cout << std::endl;
    
    IPAddress ip = {192, 168, 1, 1};
    std::cout << "IP Address: " << +ip.a << "." << +ip.b << "." << +ip.c << "." << +ip.d << std::endl;
    uint32_t ip_int = ipToInt(ip);
    std::cout << "Integer representation: " << ip_int << std::endl;
    IPAddress ip2 = intToIp(ip_int);
    std::cout << "Converted back: " << +ip2.a << "." << +ip2.b << "." << +ip2.c << "." << +ip2.d << std::endl;
    std::cout << std::endl;

    IPAddressSEC_DED packet; packet.ip = ip; intToIpSEC_DED(&packet);
    std::cout << "SEC-DED Parity: " << +packet.sec_ded << std::endl;
    packet.ip.c ^= 0x02; // Flip the least significant bit of the third octet to simulate a single-bit error
    // packet.sec_ded ^= 0x01; // Flip the least significant bit of the parity to simulate a parity error
    std::cout << "Corrupted IP Address: " << +packet.ip.a << "." << +packet.ip.b << "." << +packet.ip.c << "." << +packet.ip.d << std::endl;
    std::cout << "Corrupted SEC-DED Parity: " << +packet.sec_ded << std::endl;

    Status status = verifyAndCorrect(&packet);
    std::cout << "Verification Status: " << status << std::endl;
    std::cout << "Corrected IP Address: " << +packet.ip.a << "." << +packet.ip.b << "." << +packet.ip.c << "." << +packet.ip.d << std::endl;
    std::cout << std::endl;

    return 0;
}