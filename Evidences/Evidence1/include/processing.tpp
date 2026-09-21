#pragma once
#include <vector>
#include <bit>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>
#include <functional>

//
// -- Parser template implementations --
//
template <typename T>
std::vector<T> Parser::readLines(const std::string &filename, size_t chunkSize, std::function<T(const std::string&)> parseLine) {
    std::vector<T> results;
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(inFile, line)) {
        results.push_back(parseLine(line));
        if (results.size() >= chunkSize) {
            results.clear();
        }
    }

    return results;
}

//
// -- Algorithm template implementations --
//
template <typename T>
int Algorithm::binarySearch(const std::vector<T>& arr, T val, int p1, int p2) {
    if (p2 == -1) {p2 = arr.size() - 1;}
    if (p1 > p2) {return -1;}

    int mid = p1 + (p2-p1)/2;

    if(arr.at(mid) == val) {return mid;}
    else if(arr.at(mid) < val) {return Algorithm::binarySearch(arr, val, mid+1, p2);}
    else {return Algorithm::binarySearch(arr, val, p1, mid-1);}
}

template <typename T>
int Algorithm::partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high];
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

// -- Merge sort --
template <typename T>
void Algorithm::mergeHelper(std::vector<T> &data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void Algorithm::mergeSort(std::vector<T> &data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        Algorithm::mergeSort(data, left, mid);
        Algorithm::mergeSort(data, mid + 1, right);
        Algorithm::mergeHelper(data, left, mid, right);
    }
}

// -- intro sort --
template <typename T>
void Algorithm::introSort(std::vector<T> &data) {
    if (data.size() <= 1) return;

    int n = static_cast<int>(data.size());
    int depthLimit = 2 * (std::bit_width(static_cast<unsigned int>(n)) - 1);

    Algorithm::introSort(data, 0, n - 1, depthLimit);
}

template <typename T>
void Algorithm::introSort(std::vector<T> &data, int left, int right, int depthLimit) {
    if (right - left <= 16) {
        Algorithm::quickSort(data, left, right);
        return;
    }

    if (depthLimit == 0) {
        std::vector<T> sub(data.begin() + left, data.begin() + right + 1);
        Algorithm::heapSort(sub);
        std::copy(sub.begin(), sub.end(), data.begin() + left);
        return;
    }

    int pivot = Algorithm::partition(data, left, right);
    Algorithm::introSort(data, left, pivot - 1, depthLimit - 1);
    Algorithm::introSort(data, pivot + 1, right, depthLimit - 1);
}
