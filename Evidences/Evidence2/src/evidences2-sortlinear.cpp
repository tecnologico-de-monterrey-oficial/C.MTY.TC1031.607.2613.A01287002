#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <cctype>
#include <format>
#include <map>
#include <string>
#include "hashFunctions.h"
#include "linearDataStructures.h"

struct LogEntry {
    uint32_t ip;
    uint64_t dayTime;
    std::string response;

    bool operator<(const LogEntry &other) const { return dayTime < other.dayTime; }
    bool operator>(const LogEntry &other) const { return dayTime > other.dayTime; }
    bool operator<=(const LogEntry &other) const { return dayTime <= other.dayTime; }
};

struct RawLine {
    size_t number;
    std::string text;
};

using LogNode = std::shared_ptr<Node<LogEntry>>;

int main() {
    const char *monthNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int fileChoice = 0;
    do {
        std::cout << "Which file do you want to load?" << std::endl;
        std::cout << "  1. log607-1.txt" << std::endl;
        std::cout << "  2. log607-2.txt" << std::endl;
        std::cout << "Enter the corresponding number (1 or 2): ";

        std::string choiceInput;
        if (!std::getline(std::cin, choiceInput)) return 0;
        try {
            fileChoice = std::stoi(choiceInput);
        } catch (...) {
            fileChoice = 0;
        }
        std::cout << std::endl;

        if (fileChoice < 1 || fileChoice > 2) {
            std::cerr << "Invalid option. Try again...\n\n";
        }
    } while (fileChoice < 1 || fileChoice > 2);
    std::string filename = (fileChoice == 1) ? "data/log607-1.txt" : "data/log607-2.txt";

    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "File not found: " << filename << std::endl;
        return 1;
    }

    Queue<RawLine> lines;
    std::string text;
    size_t lineNumber = 0;
    while (std::getline(inFile, text)) {
        lines.enqueue({++lineNumber, text});
    }
    inFile.close();

    DoubleLinkedList<LogEntry> logs;
    size_t loaded = 0, skipped = 0;
    while (!lines.isEmpty()) {
        RawLine raw = lines.head->data;
        lines.dequeue();

        std::istringstream iss(raw.text);
        std::string monthStr, dayStr, yearStr, timeStr, ipStr, description, reason;
        int month = 0, day = 0, year = 0, hour = 0, minute = 0, second = 0;
        int octets[4] = {};

        if (!(iss >> monthStr >> dayStr >> yearStr >> timeStr >> ipStr)) {
            reason = "missing fields (expected: MMM DD YYYY HH:MM:SS IP description)";
        }

        if (reason.empty()) {
            for (int i = 0; i < 12; ++i) {
                if (monthStr == monthNames[i]) month = i + 1;
            }
            if (month == 0) reason = "invalid month '" + monthStr + "'";
        }

        if (reason.empty()) {
            if (yearStr.size() != 4 || yearStr.find_first_not_of("0123456789") != std::string::npos) {
                reason = "invalid year '" + yearStr + "'";
            } else {
                year = std::stoi(yearStr);
            }
        }

        if (reason.empty()) {
            if (dayStr.empty() || dayStr.size() > 2 || dayStr.find_first_not_of("0123456789") != std::string::npos) {
                reason = "invalid day '" + dayStr + "'";
            } else {
                day = std::stoi(dayStr);
                bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
                int maxDay = (month == 2 && leap) ? 29 : monthDays[month - 1];
                if (day < 1 || day > maxDay) {
                    reason = "day " + dayStr + " does not exist in " + monthStr + " " + yearStr;
                }
            }
        }

        if (reason.empty()) {
            bool validTime = timeStr.size() == 8 && timeStr[2] == ':' && timeStr[5] == ':';
            for (int p : {0, 1, 3, 4, 6, 7}) {
                if (validTime && !std::isdigit(static_cast<unsigned char>(timeStr[p]))) validTime = false;
            }
            if (!validTime) {
                reason = "invalid time format '" + timeStr + "'";
            } else {
                hour = std::stoi(timeStr.substr(0, 2));
                minute = std::stoi(timeStr.substr(3, 2));
                second = std::stoi(timeStr.substr(6, 2));
                if (hour > 23 || minute > 59 || second > 59) {
                    reason = "time out of range '" + timeStr + "'";
                }
            }
        }

        if (reason.empty()) {
            std::istringstream ipIss(ipStr);
            std::string part;
            int count = 0;
            bool validIP = ipStr.back() != '.';
            while (validIP && std::getline(ipIss, part, '.')) {
                if (count == 4 || part.empty() || part.size() > 3 ||
                    part.find_first_not_of("0123456789") != std::string::npos || std::stoi(part) > 255) {
                    validIP = false;
                } else {
                    octets[count++] = std::stoi(part);
                }
            }
            if (!validIP || count != 4) reason = "invalid IP address '" + ipStr + "'";
        }

        if (reason.empty()) {
            std::getline(iss, description);
            size_t first = description.find_first_not_of(" \t");
            size_t last = description.find_last_not_of(" \t\r");
            if (first == std::string::npos) {
                reason = "missing description";
            } else {
                description = description.substr(first, last - first + 1);
            }
        }

        if (!reason.empty()) {
            std::cerr << "   Line " << raw.number << " skipped: " << reason << std::endl;
            skipped++;
            continue;
        }

        DayTime dt = {};
        dt.year = year;
        dt.month = month;
        dt.day = day;
        dt.hour = hour;
        dt.minute = minute;
        dt.second = second;
        encodeDayTime(&dt);

        IPAddress ip = {(uint_least8_t)octets[0], (uint_least8_t)octets[1],
                        (uint_least8_t)octets[2], (uint_least8_t)octets[3]};
        logs.append({ipToInt(ip), daytimeToU64(&dt), description});
        loaded++;
    }
    std::cout << "Loaded " << loaded << " records from " << filename
              << ", skipped " << skipped << " invalid lines." << std::endl;
    std::cout << std::endl;

    bool sorted = false;
    bool hasSearch = false;
    uint64_t searchKey = 0;
    std::string searchLabel;
    DoubleLinkedList<LogEntry> results;

    int option = 0;
    do {
        do {
            std::cout << "What would you like to do?" << std::endl;
            std::cout << "  1. Sort by date and time" << std::endl;
            std::cout << "  2. Search logs by day" << std::endl;
            std::cout << "  3. Show logs by day in descending order" << std::endl;
            std::cout << "  4. File statistics" << std::endl;
            std::cout << "  5. Exit" << std::endl;
            std::cout << "Enter the corresponding number (1 to 5): ";

            std::string optionInput;
            if (!std::getline(std::cin, optionInput)) {
                option = 5;
                break;
            }
            try {
                option = std::stoi(optionInput);
            } catch (...) {
                option = 0;
            }
            std::cout << std::endl;

            if (option < 1 || option > 5) {
                std::cerr << "Invalid option. Try again...\n\n";
            }
        } while (option < 1 || option > 5);

        switch (option) {
        case 1: {
            bool alreadySorted = true;
            for (LogNode current = logs.head; current && current->next; current = current->next) {
                if (current->next->data < current->data) {
                    alreadySorted = false;
                    break;
                }
            }

            if (alreadySorted) {
                std::cout << "The list is already sorted by date and time, it will not be sorted again." << std::endl;
            } else {
                const char *algorithm = "Merge Sort";
                const char *modelNames[3] = {"n", "n log n", "n^2"};
                const int expected = 1;
                std::cout << "Sorting with " << algorithm << " (expected ~" << modelNames[expected] << " comparisons)..." << std::endl;

                size_t comparisons = 0;
                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

                LogNode dummy = std::make_shared<Node<LogEntry>>(LogEntry{});
                dummy->next = std::move(logs.head);
                logs.tail.reset();

                for (size_t width = 1; width < loaded; width *= 2) {
                    LogNode tail = dummy;
                    LogNode current = dummy->next;
                    while (current) {
                        LogNode left = current;
                        for (size_t i = 1; i < width && current->next; ++i) current = current->next;
                        LogNode right = current->next;
                        current->next.reset();

                        current = right;
                        if (current) {
                            for (size_t i = 1; i < width && current->next; ++i) current = current->next;
                            LogNode rest = current->next;
                            current->next.reset();
                            current = rest;
                        }

                        while (left && right) {
                            comparisons++;
                            if (left->data <= right->data) {
                                tail->next = left;
                                left = left->next;
                            } else {
                                tail->next = right;
                                right = right->next;
                            }
                            tail = tail->next;
                        }
                        tail->next = left ? left : right;
                        while (tail->next) tail = tail->next;
                    }
                }

                logs.head = std::move(dummy->next);
                LogNode prev;
                for (LogNode current = logs.head; current; current = current->next) {
                    current->prev = prev;
                    prev = current;
                }
                logs.tail = prev;

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;

                double n = static_cast<double>(loaded);
                double models[3] = {n, n * std::log2(n), n * n};
                int observed = 0;
                for (int i = 1; i < 3; ++i) {
                    double measured = std::log(static_cast<double>(comparisons));
                    if (std::fabs(measured - std::log(models[i])) < std::fabs(measured - std::log(models[observed]))) {
                        observed = i;
                    }
                }

                std::cout << std::format("{} | {} | n = {}\n", algorithm, filename, loaded);
                std::cout << std::format("Time: {:.2f} ms | Comparisons: {} | Max recursion depth: 0\n",
                    elapsed.count(), comparisons);
                std::cout << std::format("Expected ~{}, observed ~{}: {}\n", modelNames[expected], modelNames[observed],
                    expected == observed ? "matched" : "did not match");
                std::cout << std::endl;
            }
            sorted = true;

            std::string outputFilename = "out/output608.out";
            std::ofstream outFile(outputFilename);
            if (!outFile) {
                std::cerr << "Could not open file for writing: " << outputFilename << std::endl;
            } else {
                for (LogNode current = logs.head; current; current = current->next) {
                    DayTime dt = u64ToDayTime(current->data.dayTime);
                    IPAddress ip = u32TpIP(current->data.ip);
                    outFile << std::format("{} {:02} {:04} {:02}:{:02}:{:02} {}.{}.{}.{} {}\n",
                        monthNames[dt.month - 1], +dt.day, +dt.year, +dt.hour, +dt.minute, +dt.second,
                        +ip.a, +ip.b, +ip.c, +ip.d, current->data.response);
                }
                std::cout << "Sorted data saved to " << outputFilename << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        case 2:
        case 3: {
            if (!sorted) {
                std::cerr << "The list is not sorted yet. Please sort it first (option 1).\n\n";
                break;
            }

            if (option == 2 || !hasSearch) {
                if (option == 3) std::cout << "No search has been made yet." << std::endl;

                bool validDay = false;
                do {
                    std::cout << "Enter the day to search (format: MMM DD YYYY, e.g. Sep 14 2024): ";
                    std::string dayInput;
                    if (!std::getline(std::cin, dayInput)) return 0;

                    std::istringstream iss(dayInput);
                    std::string monthStr, dayStr, yearStr, extra;
                    std::string reason;
                    int month = 0, day = 0, year = 0;

                    if (!(iss >> monthStr >> dayStr >> yearStr) || (iss >> extra)) {
                        reason = "expected format MMM DD YYYY";
                    }
                    if (reason.empty()) {
                        for (int i = 0; i < 12; ++i) {
                            if (monthStr == monthNames[i]) month = i + 1;
                        }
                        if (month == 0) reason = "invalid month '" + monthStr + "'";
                    }
                    if (reason.empty()) {
                        if (yearStr.size() != 4 || yearStr.find_first_not_of("0123456789") != std::string::npos) {
                            reason = "invalid year '" + yearStr + "'";
                        } else {
                            year = std::stoi(yearStr);
                        }
                    }
                    if (reason.empty()) {
                        if (dayStr.size() > 2 || dayStr.find_first_not_of("0123456789") != std::string::npos) {
                            reason = "invalid day '" + dayStr + "'";
                        } else {
                            day = std::stoi(dayStr);
                            bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
                            int maxDay = (month == 2 && leap) ? 29 : monthDays[month - 1];
                            if (day < 1 || day > maxDay) {
                                reason = "day " + dayStr + " does not exist in " + monthStr + " " + yearStr;
                            }
                        }
                    }

                    if (!reason.empty()) {
                        std::cerr << "Invalid day: " << reason << ". Try again...\n\n";
                    } else {
                        DayTime dt = {};
                        dt.year = year;
                        dt.month = month;
                        dt.day = day;
                        searchKey = daytimeToU64(&dt) >> 24;
                        searchLabel = std::format("{} {:02} {:04}", monthNames[month - 1], day, year);
                        validDay = true;
                    }
                } while (!validDay);
                std::cout << std::endl;

                results.tail.reset();
                while (results.head) {
                    LogNode next = std::move(results.head->next);
                    results.head = std::move(next);
                }

                for (LogNode current = logs.head; current; current = current->next) {
                    uint64_t currentDay = current->data.dayTime >> 24;
                    if (currentDay > searchKey) break;
                    if (currentDay == searchKey) results.append(current->data);
                }
                hasSearch = true;
            }

            if (!results.head) {
                std::cout << "No logs were found for " << searchLabel << "." << std::endl;
                std::cout << std::endl;
                break;
            }

            size_t found = 0;
            if (option == 2) {
                std::cout << "Logs for " << searchLabel << ":" << std::endl;
                for (LogNode current = results.head; current; current = current->next) {
                    DayTime dt = u64ToDayTime(current->data.dayTime);
                    IPAddress ip = u32TpIP(current->data.ip);
                    std::cout << std::format("   {} {:02} {:04} {:02}:{:02}:{:02} {}.{}.{}.{} {}\n",
                        monthNames[dt.month - 1], +dt.day, +dt.year, +dt.hour, +dt.minute, +dt.second,
                        +ip.a, +ip.b, +ip.c, +ip.d, current->data.response);
                    found++;
                }
            } else {
                Stack<LogEntry> stack;
                for (LogNode current = results.head; current; current = current->next) {
                    stack.push(current->data);
                }

                std::cout << "Logs for " << searchLabel << " (descending order):" << std::endl;
                while (!stack.isEmpty()) {
                    DayTime dt = u64ToDayTime(stack.head->data.dayTime);
                    IPAddress ip = u32TpIP(stack.head->data.ip);
                    std::cout << std::format("   {} {:02} {:04} {:02}:{:02}:{:02} {}.{}.{}.{} {}\n",
                        monthNames[dt.month - 1], +dt.day, +dt.year, +dt.hour, +dt.minute, +dt.second,
                        +ip.a, +ip.b, +ip.c, +ip.d, stack.head->data.response);
                    stack.pop();
                    found++;
                }
            }
            std::cout << "Total found: " << found << std::endl;
            std::cout << std::endl;
            break;
        }
        case 4: {
            std::map<uint64_t, size_t> perDay;
            std::map<std::string, size_t> perEvent;
            std::map<uint32_t, size_t> perIP;
            size_t total = 0;
            for (LogNode current = logs.head; current; current = current->next) {
                perDay[current->data.dayTime >> 24]++;
                perEvent[current->data.response]++;
                perIP[current->data.ip]++;
                total++;
            }

            size_t maxDay = 0, maxEvent = 0, maxIP = 0;
            for (const auto &[key, count] : perDay) if (count > maxDay) maxDay = count;
            for (const auto &[key, count] : perEvent) if (count > maxEvent) maxEvent = count;
            for (const auto &[key, count] : perIP) if (count > maxIP) maxIP = count;

            std::cout << "Total records: " << total << std::endl;
            std::cout << "Day with most incidents:" << std::endl;
            for (const auto &[key, count] : perDay) {
                if (count != maxDay) continue;
                DayTime dt = u64ToDayTime(key << 24);
                std::cout << std::format("   {} {:02} {:04} ({} occurrences)\n",
                    monthNames[dt.month - 1], +dt.day, +dt.year, count);
            }
            std::cout << "Most frequent event type:" << std::endl;
            for (const auto &[key, count] : perEvent) {
                if (count != maxEvent) continue;
                std::cout << "   " << key << " (" << count << " occurrences)" << std::endl;
            }
            std::cout << "Most frequent IP address:" << std::endl;
            for (const auto &[key, count] : perIP) {
                if (count != maxIP) continue;
                std::cout << "   " << printIPAddress(u32TpIP(key)) << " (" << count << " occurrences)" << std::endl;
            }
            std::cout << std::endl;
            break;
        }
        }
    } while (option != 5);

    results.tail.reset();
    while (results.head) {
        LogNode next = std::move(results.head->next);
        results.head = std::move(next);
    }
    logs.tail.reset();
    while (logs.head) {
        LogNode next = std::move(logs.head->next);
        logs.head = std::move(next);
    }

    return 0;
}
