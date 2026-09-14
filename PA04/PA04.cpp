//these are the includes
#include <iostream>
#include <stdexcept>
#include "Fraction.h"

    Fraction(int numerator, int denominator){
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        num = numerator;
        den = denominator;
    }
    //outstream operator
    friend ostream &operator << (ostream &stream, const Fraction &other){
        stream << other.num << "/" << other.den;
        return stream;
    }

    //i recon this will make the bases the same for these two
    Fraction operator + (const Fraction & other) const{

        int newNum = num * other.den + other.num * den;
        int newDen = den * other.den;
    
        return Fraction result(newNum, newDen);
    }
    Fraction operator - (const Fraction & other) const{

        int newNum = num * other.den - other.num * den;
        int newDen = den * other.den;
    
        return Fraction result(newNum, newDen);
    }

    //this one is way easier just top times top and bottom times bottom
    Fraction operator * (const Fraction & other) const{

        //multiply nums and denoms
        int newNum = num * other.num;
        int newDen = den * other.den;

        return Fraction result(newNum, newDen); //return the new frac
    }

    //here i think we will multiply by the reciperocal
    Fraction operator / (const Fraction & other) const{

        //cross multiply
        int newNum = num * other.den;
        int newDen = den * other.num;

        return Fraction(newNum, newDen); //return finished fraction
    }

    //same trick i used for addition just checking equality now
    bool operator == (Fraction &other) const{
        return num * other.den == other.num * den;
    }

