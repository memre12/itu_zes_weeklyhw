#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    float addition(float a, float b);
    
    float subtraction(float a, float b);
    
    float multiplication(float a, float b);
    
    float division(float a, float b);
    
    float square(float a);
    
    float exponentiation(float base, float exponent);
    
    int modulus(int a, int b);
};
#endif
