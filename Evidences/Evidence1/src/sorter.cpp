#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <set>
#include "hashFunctions.h"
#include "processing.h"

struct LogEntry {
    uint32_t ip;
    uint64_t dayTime;
    std::string response;

    bool operator<(const LogEntry &other) const { return dayTime < other.dayTime; }
    bool operator>(const LogEntry &other) const { return dayTime > other.dayTime; }
    bool operator<=(const LogEntry &other) const { return dayTime <= other.dayTime; }
};

int main() {
    int mainChoice = 0;
    
    do {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "  1. Process a log file" << std::endl;
        std::cout << "  2. Search entries in log files" << std::endl;
        std::cout << "Enter the corresponding number (1 or 2): ";

        std::string mainInput;
        std::getline(std::cin, mainInput);
        if (!mainInput.empty()) {
            try {
                mainChoice = std::stoi(mainInput);
            } catch (...) {
                mainChoice = 0;
            }
        }
        std::cout << std::endl;

        if (mainChoice < 1 || mainChoice > 2) {
            std::cerr << "Invalid option. Try again...\n\n";
        }
    } while (mainChoice < 1 || mainChoice > 2);

    // Sorting process
    switch(mainChoice) {
        case 1: {
        // Which file will you use?
        std::string filename;
        int choice = 0;
        do {
            std::cout << "Which file do you want to process?" << std::endl;
            std::cout << "  1. log607-1.txt" << std::endl;
            std::cout << "  2. log607-2.txt" << std::endl;
            std::cout << "Enter the corresponding number (1 or 2): ";

            std::string choiceInput;
            std::getline(std::cin, choiceInput);
            if (!choiceInput.empty()) {
                try {
                    choice = std::stoi(choiceInput);
                } catch (...) {
                    choice = 0;
                }
            }
            std::cout << std::endl;

            if (choice < 1 || choice > 2) {
                std::cerr << "Invalid option. Try again...\n\n";
            }
        } while (choice < 1 || choice > 2);
        filename = (choice == 1) ? "data/log607-1.txt" : "data/log607-2.txt";
        
        // File reading and processing
        Parser parser(filename);
        std::vector<uint32_t> numericIPAddresses;
        std::vector<uint64_t> numericDayTimes;
        std::vector<std::string> responses;
        parser.readLogEntries(filename, numericIPAddresses, numericDayTimes, responses);

        std::cout << "Head, showing 6 of " << responses.size() << " entries from " << filename << std::endl;
        for(size_t i = 0; i < 6; ++i) {
            std::cout << "   IP: " << printIPAddress(u32TpIP(numericIPAddresses[i])) 
                    << "   DayTime: " << printDayTime(u64ToDayTime(numericDayTimes[i]))
                    << "   Response: " << responses[i]
                    << std::endl;
        }

        std::cout << std::endl;
        
        // Which sorting algorithm do you want to use?
        int sortChoice = 0;
        do {
            std::cout << "Which sorting algorithm do you want to use?" << std::endl;
            std::cout << "  1. Quick Sort" << std::endl;
            std::cout << "  2. Heap Sort" << std::endl;
            std::cout << "  3. Merge Sort" << std::endl;
            std::cout << "  4. Intro Sort" << std::endl;
            std::cout << "  5. Swap Sort" << std::endl;
            std::cout << "  6. Bubble Sort" << std::endl;
            std::cout << "  7. Selection Sort" << std::endl;
            std::cout << "  8. Insertion Sort" << std::endl;
            std::cout << "Enter the corresponding number (1 to 8): ";
            std::string sortInput;
            std::getline(std::cin, sortInput);
            if (!sortInput.empty()) {
                try {
                    sortChoice = std::stoi(sortInput);
                } catch (...) {
                    sortChoice = 0;
                }
            }
            std::cout << std::endl;

            if (sortChoice < 1 || sortChoice > 4) {
                std::cerr << "Invalid option. Try again...\n\n";
            }
        } while (sortChoice < 1 || sortChoice > 4);

        // Pack parallel vectors into a single sortable vector
        std::vector<LogEntry> entries(numericIPAddresses.size());
        for (size_t i = 0; i < numericIPAddresses.size(); ++i) {
            entries[i] = {numericIPAddresses[i], numericDayTimes[i], responses[i]};
        }

        // Run the selected sorting algorithm
        Algorithm algorithm;

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        switch (sortChoice) {
            case 1:
                algorithm.quickSort(entries, 0, entries.size() - 1);
                break;
            case 2:
                algorithm.heapSort(entries);
                break;
            case 3:
                algorithm.mergeSort(entries, 0, entries.size() - 1);
                break;
            case 4:
                algorithm.introSort(entries);
                break;
            case 5:
                algorithm.swapSort(entries);
                break;
            case 6:
                algorithm.bubbleSort(entries);
                break;
            case 7:
                algorithm.selectionSort(entries);
                break;
            case 8:
                algorithm.insertionSort(entries);
                break; 
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        // Unpack back into the original parallel vectors
        for (size_t i = 0; i < entries.size(); ++i) {
            numericIPAddresses[i] = entries[i].ip;
            numericDayTimes[i] = entries[i].dayTime;
            responses[i] = std::move(entries[i].response);
        }

        std::cout << "Tail, showing 6 of " << responses.size() << " entries from " << filename << std::endl;
        for(size_t i = responses.size() - 6; i < responses.size(); ++i) {
            std::cout << "   IP: " << printIPAddress(u32TpIP(numericIPAddresses[i])) 
                    << "   DayTime: " << printDayTime(u64ToDayTime(numericDayTimes[i]))
                    << "   Response: " << responses[i]
                    << std::endl;
        }
        std::cout << std::endl;

        switch (sortChoice) {
            case 1:
                std::cout << "Algorithm used: Quick Sort" << std::endl;
                std::cout << "   Average time complexity: O(n log n)" << std::endl;
                std::cout << "   Average space complexity: O(log n)" << std::endl;
                std::cout << "   Best time complexity    : O(n log n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n^2)" << std::endl;
                break;
            case 2:
                std::cout << "Algorithm used: Heap Sort" << std::endl;
                std::cout << "   Average time complexity: O(n log n)" << std::endl;
                std::cout << "   Average space complexity: O(1)" << std::endl;
                std::cout << "   Best time complexity    : O(n log n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n log n)" << std::endl;
                break;
            case 3:
                std::cout << "Algorithm used: Merge Sort" << std::endl;
                std::cout << "   Average time complexity: O(n log n)" << std::endl;
                std::cout << "   Average space complexity: O(n)" << std::endl;
                std::cout << "   Best time complexity    : O(n log n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n log n)" << std::endl;
                break;
            case 4:
                std::cout << "Algorithm used: Intro Sort" << std::endl;
                std::cout << "   Average time complexity: O(n log n)" << std::endl;
                std::cout << "   Average space complexity: O(log n)" << std::endl;
                std::cout << "   Best time complexity    : O(n log n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n log n)" << std::endl;
                break;
            case 5:
                std::cout << "Algorithm used: Swap Sort" << std::endl;
                std::cout << "   Average time complexity: O(n^2)" << std::endl;
                std::cout << "   Average space complexity: O(1)" << std::endl;
                std::cout << "   Best time complexity    : O(n^2)" << std::endl;
                std::cout << "   Worst time complexity   : O(n^2)" << std::endl;
                break;
            case 6:
                std::cout << "Algorithm used: Bubble Sort" << std::endl;
                std::cout << "   Average time complexity: O(n^2)" << std::endl;
                std::cout << "   Average space complexity: O(1)" << std::endl;
                std::cout << "   Best time complexity    : O(n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n^2)" << std::endl;
                break;
            case 7:
                std::cout << "Algorithm used: Selection Sort" << std::endl;
                std::cout << "   Average time complexity: O(n^2)" << std::endl;
                std::cout << "   Average space complexity: O(1)" << std::endl;
                std::cout << "   Best time complexity    : O(n^2)" << std::endl;
                std::cout << "   Worst time complexity   : O(n^2)" << std::endl;
                break;
            case 8:
                std::cout << "Algorithm used: Insertion Sort" << std::endl;
                std::cout << "   Average time complexity: O(n^2)" << std::endl;
                std::cout << "   Average space complexity: O(1)" << std::endl;
                std::cout << "   Best time complexity    : O(n)" << std::endl;
                std::cout << "   Worst time complexity   : O(n^2)" << std::endl;
                break;
        }

        // Save results to /out/output608.txt
        std::string outputFilename = "out/output608.txt";    
        parser.saveFile(outputFilename, numericIPAddresses, numericDayTimes, responses);
        std::cout << "Results saved to " << outputFilename << std::endl;
        std::cout << std::endl;

        std::cout << "Execution time: " << elapsed_seconds.count() << " seconds" << std::endl;
        std::cout << std::endl;

        auto duplicate = [](const std::vector<uint64_t>& daytimes) {
            std::set<uint64_t> seen;
            std::vector<uint64_t> duplicates;

            for (const auto& dt : daytimes) {
                if (!seen.insert(dt).second) {
                    duplicates.push_back(dt);
                }
            }

            return duplicates;
        };

        std::cout << "Checking for duplicates in DayTimes..." << std::endl;
        std::vector<uint64_t> duplicates = duplicate(numericDayTimes);
        std::cout << "Found " << duplicates.size() << " duplicates in DayTimes." << std::endl;
        if (!duplicates.empty()) {
            std::cout << "Showing up to 5 duplicates:" << std::endl;
            for (size_t i = 0; i < std::min<size_t>(5, duplicates.size()); ++i) {
                std::cout << "   " << printDayTime(u64ToDayTime(duplicates[i])) << std::endl;
            }
        }
        std::cout << std::endl;

        break;
        }
    case 2: {
        // Does /out/output608.txt exist?
        if(!std::ifstream("out/output608.txt")) {
            std::cerr << "Processed log file not found. Please process a file first." << std::endl;
            return 1;
        }
        std::cout << "Processed log file found. Starting search..." << std::endl;

        // Choose date and time
        std::string dateTimeInput;
        bool isValid = false;
        do {
            std::cout << "Enter the date and time to search (format: YYYY-MM-DD HH:MM:SS): ";
            std::getline(std::cin, dateTimeInput);
            isValid = (dateTimeInput.length() == 19 &&
                    dateTimeInput[4] == '-' && dateTimeInput[7] == '-' &&
                    dateTimeInput[10] == ' ' && dateTimeInput[13] == ':' && 
                    dateTimeInput[16] == ':');
            if (!isValid) {
                std::cerr << "Invalid format. Please use YYYY-MM-DD HH:MM:SS.\n";
            } else {
                std::cout << "Date and time entered: " << dateTimeInput << std::endl;
            }
        } while (!isValid);
        
        // Parse user input to DayTime and then to uint64_t
        DayTime searchDT = {};
        searchDT.year   = std::stoi(dateTimeInput.substr(0, 4));
        searchDT.month  = std::stoi(dateTimeInput.substr(5, 2));
        searchDT.day    = std::stoi(dateTimeInput.substr(8, 2));
        searchDT.hour   = std::stoi(dateTimeInput.substr(11, 2));
        searchDT.minute = std::stoi(dateTimeInput.substr(14, 2));
        searchDT.second = std::stoi(dateTimeInput.substr(17, 2));
        encodeDayTime(&searchDT);
        uint64_t searchKey = daytimeToU64(&searchDT);

        // Read the output file into parallel vectors (already sorted)
        Parser outParser("out/output608.txt");
        std::vector<uint32_t> ips;
        std::vector<uint64_t> daytimes;
        std::vector<std::string> responses;
        outParser.readOutputFile("out/output608.txt", ips, daytimes, responses);

        // Search by Binary Search
        Algorithm algorithm;
        std::cout << "Searching entries for: " << dateTimeInput << std::endl;
        int idx = algorithm.binarySearch(daytimes, searchKey);

        if (idx == -1) {
            std::cout << "No entries were found for the specified date and time." << std::endl;
        } else {
            // Expand to the left to find all matches
            int left = idx;
            while (left > 0 && daytimes[left - 1] == searchKey) left--;

            // Expand to the right to find all matches
            int right = idx;
            while (right < (int)daytimes.size() - 1 && daytimes[right + 1] == searchKey) right++;

            int count = right - left + 1;
            std::cout << "Found " << count << " matching entries:" << std::endl;
            std::cout << std::endl;
            for (int i = left; i <= right; ++i) {
                std::cout << "   IP: " << printIPAddress(u32TpIP(ips[i]))
                          << "   DayTime: " << printDayTime(u64ToDayTime(daytimes[i]))
                          << "   Response: " << responses[i]
                          << std::endl;
            }
            std::cout << std::endl;

            std::cout << "Saved search results to out/range607.txt" << std::endl;
            std::ofstream outFile("out/range607.txt");
            if (outFile.is_open()) {
                outFile << "Search results for: " << dateTimeInput << std::endl;
                outFile << std::endl;
                for (int i = left; i <= right; ++i) {
                    outFile << "   IP: " << printIPAddress(u32TpIP(ips[i]))
                            << "   DayTime: " << printDayTime(u64ToDayTime(daytimes[i]))
                            << "   Response: " << responses[i]
                            << std::endl;
                }
                outFile.close();
            }
        }

        break;    
    }}
        
    return 0;
}