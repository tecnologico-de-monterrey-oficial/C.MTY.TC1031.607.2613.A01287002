#include "lib/hashFunctions.h"
#include <iostream>

int main() {
    // --------------
    // Test IP Address
    // --------------
    IPAddress ip = {192, 168, 1, 1};
    std::cout << "IP Address: " << printIPAddress(ip) << std::endl;
    uint32_t ip_int = ipToInt(ip);
    std::cout << "Integer representation: " << ip_int << std::endl;
    IPAddress ip2 = intToIp(ip_int);
    std::cout << "Converted back: " << printIPAddress(ip2) << std::endl;
    std::cout << std::endl;

    IPAddressSEC_DED packet; packet.ip = ip; intToIpSEC_DED(&packet);
    std::cout << "SEC-DED Parity: " << +packet.sec_ded << std::endl;
    packet.ip.c ^= 0x02; // Flip the least significant bit of the third octet to simulate a single-bit error
    // packet.sec_ded ^= 0x01; // Flip the least significant bit of the parity to simulate a parity error
    std::cout << "Corrupted IP Address: " << printIPAddress(packet.ip) << std::endl;
    std::cout << "Corrupted SEC-DED Parity: " << +packet.sec_ded << std::endl;

    Status status = verifyAndCorrect(&packet);
    std::cout << "Verification Status: " << prettyPrintStatus(status) << std::endl;
    std::cout << "Corrected IP Address: " << printIPAddress(packet.ip) << std::endl;
    std::cout << std::endl;

    // --------------
    // Test DayTime
    // --------------
    DayTime dt = {2024, 2, 29, 14, 30, 45};
    std::cout << "DayTime: " << printDayTime(dt) << std::endl;
    encodeDayTime(&dt);
    std::cout << "SEC-DED Parity: " << +dt.sec_ded << std::endl;

    // Simulate a single-bit error
    dt.month ^= 0x01;
    std::cout << "Corrupted DayTime: " << printDayTime(dt) << std::endl;
    std::cout << "Corrupted SEC-DED Parity: " << +dt.sec_ded << std::endl;

    Status status2 = verifyAndCorrectDayTime(&dt);
    std::cout << "Verification Status: " << prettyPrintStatus(status2) << std::endl;
    std::cout << "Corrected DayTime: " << printDayTime(dt) << std::endl;
    std::cout<<std::endl;

    return 0;
}