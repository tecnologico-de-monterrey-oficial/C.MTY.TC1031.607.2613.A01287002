/*
#   Activity 1.2 - Recursion
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: main.cpp
#   
#   Created:                   18/04/2026
#   Last Modified:             18/04/2024
*/

#include "helper.h"
#include <iostream>

int main() {
    int n = 16; int m = 5; double investment = 1000;
    std::cout << "Suma (Iterativa): " << sumIterative(n) << std::endl;
    std::cout << "Suma (Recursiva): " << sumRecursive(n) << std::endl;
    std::cout << "Suma (Formula): " << sumFormula(n) << std::endl;

    std::cout << "Fibonacci (Iterativa): " << fibonacciIterative(n) << std::endl;
    std::cout << "Fibonacci (Recursiva): " << fibonacciRecursive(n) << std::endl;

    std::cout << "Crecimiento de Bacterias después de " << n << " días (Iterativo): " << bacteriaGrowth(n) << std::endl;
    std::cout << "Crecimiento de Bacterias después de " << n << " días (Recursivo): " << bacteriasRecursive(n) << std::endl;

    std::cout << "Crecimiento de la Inversión después de " << n << " meses (Iterativo): " << investmentIterative(investment, n) << std::endl;
    std::cout << "Crecimiento de la Inversión después de " << n << " meses (Recursivo): " << investmentRecursive(investment, n) << std::endl;

    std::cout << "Potencia (Iterativa): " << powIterative(n, m) << std::endl;
    std::cout << "Potencia (Recursiva): " << powRecursive(n, m) << std::endl;
    return 0;
}