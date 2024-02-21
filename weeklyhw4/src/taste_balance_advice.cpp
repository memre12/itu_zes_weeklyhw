#include "taste_balance_advice.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <calculation.hpp>


void taste_balance_advice::general_adivce(){
    advice("starters");
    
}

void taste_balance_advice::advice(const std::string& category) {
    calculation exmp;
    exmp.fill_vectors(category);
    
    
    int minError = std::numeric_limits<int>::max();
    int minItemIndex = -1;

    // Display taste balance values and calculate errors
    for (int j = 0; j < 5; j++) {
        std::vector<int> errors(5, 0); // Vector to store errors for each item

        for (int i = 0; i < 5; i++) {
            errors[j] += abs(exmp.willaddtaste_balance_total[j][i] - choice[i]);
        }

        // Check for the minimum error
        if (errors[j] < minError) {
            minError = errors[j];
            minItemIndex = j + 1;
        }
    }
    recommendation = minItemIndex;
}

int taste_balance_advice::get_recommendation() {
    return recommendation;
}

void taste_balance_advice::set_preference() {
    std::vector<int> preference;
    // Use a vector to store taste balance values
    std::vector<int> tasteBalanceValues;
    int sweet,sour,bitter,salty,savory;

    
    while (true)
    {
        std::cout << "Please input your taste_balance values (values shoulde be between 1-10)" << std::endl;  
        std::cout << "Sweet: ";
        std::cin >> sweet;              
        if (sweet>0 && sweet<=10)
        {
            preference.push_back(sweet);
            break;
        }else{
            std::cerr << "TRY AGAIN!!!\nInvalid value, value shoulde be between 1-10" << std::endl;
        }
    }

    while (true)
    {
        std::cout << "\nSour: ";
        std::cin >> sour;
        if (sour>0 && sour<=10)
        {
            preference.push_back(sour);
            break;
        }else{
            std::cerr << "TRY AGAIN!!!\nInvalid value, value shoulde be between 1-10" << std::endl;
        }
    }

    while (true)
    {
        std::cout << "\nBitter: ";
        std::cin >> bitter;
        if (bitter>0 && bitter<=10)
        {
            preference.push_back(bitter);
            break;
        }else{
            std::cerr << "TRY AGAIN!!!\nInvalid value, value shoulde be between 1-10" << std::endl;
        }
    }

    while (true)
    {
        std::cout << "\nSalty: ";
        std::cin >> salty;
        if (salty>0 && salty<=10)
        {
            preference.push_back(salty);
            break;
        }else{
            std::cerr << "TRY AGAIN!!!\nInvalid value, value shoulde be between 1-10" << std::endl;
        }
    }

    while (true)
    { 
        std::cout << "\nSavory: ";
        std::cin >> savory;
        if (savory>0 && savory<=10)
        {
            preference.push_back(savory);
            break;
        }else{
            std::cerr << "TRY AGAIN!!!\nInvalid value, value shoulde be between 1-10" << std::endl;
        }
    }
    choice = std::move(preference);
}