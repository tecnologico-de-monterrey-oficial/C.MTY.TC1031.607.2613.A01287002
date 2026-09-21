#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <memory>
#include <bit> 
#include "hashFunctions.h"

class Parser {
private:
    std::ifstream file;

public:
    Parser(const std::string &filename);
    ~Parser();

    bool findFile(const std::string &filename);
    void readFileInChunks(size_t chunkSize, std::function<void(const char*, size_t)> processChunk);

    template <typename T>
    std::vector<T> readLines(const std::string &filename, size_t chunkSize, std::function<T(const std::string&)> parseLine);
    
    void saveFile(const std::string &filename, const std::vector<uint32_t> &numericIPAddresses, const std::vector<uint64_t> &numericDayTimes, const std::vector<std::string> &responses);
    std::vector<std::string> readResponses(const std::string &filename, size_t chunkSize);

    std::vector<uint32_t> readNumericIPAddresses(const std::string &filename, size_t chunkSize);
    std::vector<uint64_t> readNumericDayTimes(const std::string &filename, size_t chunkSize);

    DayTime parseLogLine(const std::string &line);
    uint32_t parseLogIP(const std::string &line);
    void readLogEntries(const std::string &filename, std::vector<uint32_t> &ips, std::vector<uint64_t> &daytimes, std::vector<std::string> &responses);

    void readOutputFile(const std::string &filename, std::vector<uint32_t> &ips, std::vector<uint64_t> &daytimes, std::vector<std::string> &responses);
};

class Algorithm {
private:
    std::vector<uint32_t> numericIPs;
    std::vector<uint64_t> numericDayTimes;

public: 
    template <typename T>
    int binarySearch(const std::vector<T>& arr, T val, int p1=0, int p2= -1);
    
    // -- quick sort --
    template <typename T>
    int partition(std::vector<T>& arr, int low, int high);
    template <typename T>
    void quickSort(std::vector<T> &data, int left, int right);

    // -- heap sort --
    template <typename T>
    void heapify(std::vector<T> &data, int n, int i);

    template <typename T>
    void heapSort(std::vector<T> &data);

    // -- Merge sort --
    template <typename T>
    void mergeHelper(std::vector<T> &data, int left, int mid, int right);

    template <typename T>
    void mergeSort(std::vector<T> &data, int left, int right);

    // -- intro sort --
    template <typename T>
    void introSort(std::vector<T> &data);

    template <typename T>
    void introSort(std::vector<T> &data, int left, int right, int depthLimit);
};

#include "processing.tpp"