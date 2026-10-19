#include "hashFunctions.h"
#include <iostream>
#include <format>

auto flipBit = [](auto& obj, std::size_t bit_index) {
    auto* bytes = reinterpret_cast<uint8_t*>(&obj);
    bytes[bit_index / 8] ^= (1U << (bit_index % 8));
};

int main() {
    // --------------
    // Test IP Address
    // --------------
    IPAddress ip = {192, 168, 1, 1};
    std::cout << "IP Address: " << printIPAddress(ip) << std::endl;
    uint32_t ip_int = ipToInt(ip);
    std::cout << "Integer representation: " << ip_int << std::endl;
    IPAddress ip2 = u32TpIP(ip_int);
    std::cout << "Converted back: " << printIPAddress(ip2) << std::endl;
    std::cout << std::endl;

    IPAddressSEC_DED packet; packet.ip = ip; u32TpIPSEC_DED(&packet);
    std::cout << "SEC-DED Parity: " << +packet.sec_ded << std::endl;
    flipBit(packet, 5); // Simulate a single-bit error
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
    uint64_t dt_int = daytimeToU64(&dt);
    std::cout << "DayTime: " << printDayTime(dt) << std::endl;
    std::cout << "Integer representation: " << dt_int << std::endl;
    encodeDayTime(&dt);
    std::cout << "SEC-DED Parity: " << +dt.sec_ded << std::endl;

    // Simulate a single-bit error
    flipBit(dt, 8);
    std::cout << "Corrupted DayTime: " << printDayTime(dt) << std::endl;
    // std::cout << "Corrupted Integer representation: " << std::format("{:b}", daytimeToU64(&dt)) << std::endl;
    std::cout << "Corrupted Integer representation: " << daytimeToU64(&dt) << std::endl;
    std::cout << "Corrupted SEC-DED Parity: " << +dt.sec_ded << std::endl;

    Status status2 = verifyAndCorrectDayTime(&dt);
    std::cout << "Verification Status: " << prettyPrintStatus(status2) << std::endl;
    // std::cout << "Corrected Integer representation: " << std::format("{:b}", daytimeToU64(&dt)) << std::endl;
    std::cout << "Corrected Integer representation: " << daytimeToU64(&dt) << std::endl;
    std::cout << "Back to Daytime: " << printDayTime(u64ToDayTime(dt_int)) << std::endl;
    std::cout<<std::endl;

    return 0;
}