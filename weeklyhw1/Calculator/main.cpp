#include <iostream>
#include <cstdlib>
#include "Calculator.h"

using namespace std;

int main() {
    Calculator calculator;
    char operation;
    float num1, num2;
    bool continueCalculation = true;

    while (continueCalculation) {
        std::cout << "Enter operation (+, -, *, /, ^, %, s for square): ";
        std::cin >> operation;

        if (operation == 's') {
            std::cout << "Enter a number: ";
            std::cin >> num1;
        } else {
            std::cout << "Enter two numbers: ";
            std::cin >> num1 >> num2;
        }

        try {
            switch (operation) {
                case '+':
                    std::cout << "Result: " << calculator.addition(num1, num2) << std::endl;
                    break;
                case '-':
                    std::cout << "Result: " << calculator.subtraction(num1, num2) << std::endl;
                    break;
                case '*':
                    std::cout << "Result: " << calculator.multiplication(num1, num2) << std::endl;
                    break;
                case '/':
                    std::cout << "Result: " << calculator.division(num1, num2) << std::endl;
                    break;
                case '^':
                    std::cout << "Result: " << calculator.exponentiation(num1, static_cast<float>(num2)) << std::endl;
                    break;
                case '%':
                    std::cout << "Result: " << calculator.modulus(static_cast<int>(num1), static_cast<int>(num2)) << std::endl;
                    break;
                case 's':
                    std::cout << "Result: " << calculator.square(num1) << std::endl;
                    break;
                default:
                    std::cout << "Invalid operation." << std::endl;
            }
        } catch (const char* e) {
            std::cerr << "Error: " << e << std::endl;
        }

        std::cout << "Do you want to perform another calculation? (Y/N): ";
        char choice;
        std::cin >> choice;
        continueCalculation = (choice == 'Y' || choice == 'y');
    }
    std::cout << "See you :) :) :)" << std::endl;
    return 0;
}
