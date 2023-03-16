#include "ComplexNumber.hpp"

ComplexNumber::ComplexNumber()
{
    r = 0;
    i = 0;
}

ComplexNumber::ComplexNumber(double real, double imaginary)
{
    r = real;
    i = imaginary;
}