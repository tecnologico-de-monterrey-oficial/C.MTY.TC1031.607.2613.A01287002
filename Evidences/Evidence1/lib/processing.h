#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <bit> 
#include "lib/hashFunctions.h"

class Parser {
private:
    std::ifstream file;

public:
    Parser(const std::string &filename);
    ~Parser();

    bool findFile(const std::string &filename);

    // Motivation is for large files, avoids a memory spike
    template <typename Callback>
    void readFileInChunks(const std::string &filename, size_t chunkSize, Callback processChunk);
    
    std::vector<uint32_t> readNumericIPAddresses(const std::string &filename, size_t chunkSize);
    std::vector<uint64_t> readNumericDayTimes(const std::string &filename, size_t chunkSize);
};

class Algorithm {
private:
    std::vector<uint32_t> numericIPs;
    std::vector<uint64_t> numericDayTimes;

public: 
    template <typename T>
    int binarySearch(const std::vector<T>& arr, T val, int p1=0, int p2= -1);
    
    // -- quick sort --
    int partition(std::vector<int>& arr, int low, int high);
    template <typename T>
    void quickSort(std::vector<T> &data, int left, int right);

    // -- heap sort --
    template <typename T>
    void heapify(std::vector<T> &data, int n, int i);

    template <typename T>
    void heapSort(std::vector<T> &data);

    // -- intro sort --
    template <typename T>
    void introSort(std::vector<T> &data);

    template <typename T>
    void introSort(std::vector<T> &data, int left, int right, int depthLimit);
};