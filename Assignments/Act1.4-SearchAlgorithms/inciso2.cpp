#include <iostream>
#include <string>
#include <algorithm>
#include "helper.h"

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore(); // Ignorar el salto de línea después de leer n

    for (int i = 0; i < n; ++i) {
        std::string str;
        std::getline(std::cin, str);

        char uniqueChar = '\0';
        int sequentialComparisons = 0;
        int binaryComparisons = 0;

        // Búsqueda secuencial
        for (int j = 0; j < str.length(); ++j) {
            sequentialComparisons++;
            if ((j == 0 || str[j] != str[j - 1]) && (j == str.length() - 1 || str[j] != str[j + 1])) {
                uniqueChar = str[j];
                break;
            }
        }

        // Búsqueda binaria
        std::sort(str.begin(), str.end());
        int left = 0, right = str.length() - 1;
        while (left <= right) {
            binaryComparisons++;
            int mid = left + (right - left) / 2;
            if ((mid == 0 || str[mid] != str[mid - 1]) && (mid == str.length() - 1 || str[mid] != str[mid + 1])) {
                uniqueChar = str[mid];
                break;
            } else if (mid > 0 && str[mid] == str[mid - 1]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        std::cout << uniqueChar << " " << sequentialComparisons << " ";
        std::cout << uniqueChar << " " << binaryComparisons << std::endl;
    }

    return 0;
}