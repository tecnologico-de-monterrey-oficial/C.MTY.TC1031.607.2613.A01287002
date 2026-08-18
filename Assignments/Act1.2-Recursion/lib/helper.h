/*
#   Activity 1.2 - Recursion
#   Andrés Rodríguez Cantú 
#   
#   Copyright (C) Tecnólogico de Monterrey
#   
#   File: lib/helper.h
#   
#   Created:                   18/04/2026
#   Last Modified:             18/04/2024
*/

#pragma once 
#include <iostream>

int sumIterative(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int sumRecursive(int n) {
    int sum = 0;
    if(n > 0) {
        sum = n + sumRecursive(n - 1);
    }
    return sum;
}

int sumFormula(int n) {
    return (n * (n + 1)) / 2;
}

int fibonacciIterative(int n) {
    if(n <= 0) return 0;
    if(n == 1) return 1;

    int a = 0, b = 1, c;
    for(int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int fibonacciRecursive(int n) {
    if(n <= 0) return 0;
    if(n == 1) return 1;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

static constexpr int GROWTH_RATE = 378;
static constexpr int DEATH_RATE = 234; 
int bacteriaGrowth(int n) {
    int bacteria = 1;
    for(int i = 0; i < n; i++) {
        int newBacteria = (bacteria * GROWTH_RATE) / 100;
        int deadBacteria = (bacteria * DEATH_RATE) / 100;
        bacteria += newBacteria - deadBacteria;
    }
    return bacteria;
}

int bacteriasRecursive(int n) {
    if(n == 0) return 1;
    int pBacteria = bacteriasRecursive(n - 1); 
    int newBacteria = (pBacteria * GROWTH_RATE) / 100;
    int deadBacteria = (pBacteria * DEATH_RATE) / 100;
    return pBacteria + newBacteria - deadBacteria;
}

static constexpr double MONTHLY_INTEREST_RATE = 18.75; 
double investmentIterative(double initialInvestment, int months) {
    double totalInvestment = initialInvestment;
    for(int i = 0; i < months; i++) {
        totalInvestment += (totalInvestment * MONTHLY_INTEREST_RATE) / 100;
    }
    return totalInvestment;
}

double investmentRecursive(double initialInvestment, int months) {
    if(months == 0) return initialInvestment;
    double pInvestment = investmentRecursive(initialInvestment, months - 1);
    return pInvestment + (pInvestment * MONTHLY_INTEREST_RATE) / 100;
}

double powIterative(int a, int b) {
    double result = 1.0;
    for(int i = 0; i < b; i++) {
        result *= a; 
    }
    return result;
}

double powRecursive(int a, int b) {
    if(b == 0) return 1.0;
    return a * powRecursive(a, b - 1);
}