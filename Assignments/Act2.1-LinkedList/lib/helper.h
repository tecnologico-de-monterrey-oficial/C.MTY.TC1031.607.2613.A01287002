#pragma once
#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int denom) : numerator(num), denominator(denom) {}

    int getNumerator() const {return numerator;}
    int getDenominator() const {return denominator;}
    void setNumerator(int num) {numerator = num;}
    void setDenominator(int denom) {denominator = denom;}

    void print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }
};