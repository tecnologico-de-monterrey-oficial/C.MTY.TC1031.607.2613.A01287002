#include "processing.h"

//
// -- Parser class implementation --
//
Parser::Parser(const std::string &filename) {
    if (!findFile(filename)) {
        throw std::runtime_error("File not found: " + filename);
    }
}

Parser::~Parser() {
    if (file.is_open()) {
        file.close();
    }
}

bool Parser::findFile(const std::string &filename) {
    std::ifstream testFile(filename);
    return testFile.good();
}

template <typename Callback>
void Parser::readFileInChunks(const std::string &filename, size_t chunkSize, Callback processChunk) {
    std::ifstream file(filename, std::ios::binary);

    std::vector<char> buffer(chunkSize);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        processChunk(buffer.data(), file.gcount());
    }
}

std::vector<uint32_t> Parser::readNumericIPAddresses(const std::string &filename, size_t chunkSize) {
    std::vector<uint32_t> ipAddresses;
    readFileInChunks(filename, chunkSize, [&ipAddresses](const char* data, size_t count) {
        for (size_t i = 0; i < count; i += sizeof(uint32_t)) {
            uint32_t ip = *reinterpret_cast<const uint32_t*>(data + i);
            ipAddresses.push_back(ip);
        }
    });
    return ipAddresses;
}

std::vector<uint64_t> Parser::readNumericDayTimes(const std::string &filename, size_t chunkSize) {
    std::vector<uint64_t> dayTimes;
    readFileInChunks(filename, chunkSize, [&dayTimes](const char* data, size_t count) {
        for (size_t i = 0; i < count; i += sizeof(uint64_t)) {
            uint64_t dt = *reinterpret_cast<const uint64_t*>(data + i);
            dayTimes.push_back(dt);
        }
    });
    return dayTimes;
}

//
// -- Algorithm class implementation --
//
template <typename T>
int Algorithm::binarySearch(const std::vector<T>& arr, T val, int p1=0, int p2= -1) {
    if (p2 == -1) {p2 = arr.size() - 1;}
    if (p1 > p2) {return -1;}
    
    int mid = p1+ (p2-p1)/2;

    if(arr.at(mid) == val) {return mid;} 
    else if(arr.at(mid) < val) {return Algorithm::binarySearch(arr, val, mid+1, p2);} 
    else {return Algorithm::binarySearch(arr, val, p1, mid-1);}
}


int Algorithm::partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void Algorithm::quickSort(std::vector<T> &data, int left, int right) {
    if (left < right) {
        int pi = Algorithm::partition(data, left, right);
        Algorithm::quickSort(data, left, pi - 1);
        Algorithm::quickSort(data, pi + 1, right);
    }
}

template <typename T>
void Algorithm::heapify(std::vector<T> &data, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l] > data[largest]) {
        largest = l;
    }

    if (r < n && data[r] > data[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(data[i], data[largest]);
        Algorithm::heapify(data, n, largest);
    }
}

template <typename T>
void Algorithm::heapSort(std::vector<T> &data) {
    int n = data.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        Algorithm::heapify(data, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(data[0], data[i]);
        Algorithm::heapify(data, i, 0);
    }
}

// -- intro sort --
// depthLimit is typically set to 2 * floor(log(n)) where n is the number of elements in the array
// Public entry point for full vector
template <typename T>
void Algorithm::introSort(std::vector<T> &data) {
    if (data.size() <= 1) return;

    int n = static_cast<int>(data.size());
    int depthLimit = 2 * (std::bit_width(static_cast<unsigned int>(n)) - 1); // log_2(n) approximation

    Algorithm::introSort(data, 0, n - 1, depthLimit);
}

// Recursive helper
template <typename T>
void Algorithm::introSort(std::vector<T> &data, int left, int right, int depthLimit) {
    if (right - left <= 16) {
        Algorithm::quickSort(data, left, right); // Note: Insertion sort is typically used here
        return;
    }

    if (depthLimit == 0) {
        Algorithm::heapSort(data, left, right); // Passed bounds to heapify subrange
        return;
    }

    int pivot = Algorithm::partition(data, left, right);
    Algorithm::introSort(data, left, pivot - 1, depthLimit - 1);
    Algorithm::introSort(data, pivot + 1, right, depthLimit - 1);
}