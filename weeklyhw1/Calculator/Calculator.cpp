#include "Calculator.h"

float Calculator::addition(float a, float b) {
    return a + b;
}

float Calculator::subtraction(float a, float b) {
    return a - b;
}

float Calculator::multiplication(float a, float b) {
    return a * b;
}

float Calculator::division(float a, float b) {
    if (b == 0) {
        throw "Division by zero is not allowed.";
    }
    return a / b;
}

float Calculator::square(float a) {
    return a * a;
}

float Calculator::exponentiation(float base, float exponent) {
    float result = 1.0;
    for (int i = 0; i < static_cast<int>(exponent); i++) {
        result *= base;
    }
    return result;
}


int Calculator::modulus(int a, int b) {
    if (b == 0) {
        throw "Modulus by zero is not allowed.";
    }
    return a % b;
}
