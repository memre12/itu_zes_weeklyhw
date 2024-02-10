#include "taste_balance_advice.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>


void taste_balance_advice::advice(const std::string& category) {
    // Define enum for taste categories
    const std::vector<std::string> tasteCategories = { "sweet", "sour", "bitter", "salty", "savory" };
    std::vector<int> preference;
    // Use a vector to store taste balance values
    std::vector<int> tasteBalanceValues;
    preference = std::move(choice);
    
    // Read the JSON file
    std::ifstream ifs("menu.json");
    if (!ifs.is_open()) {
        std::cerr << "Unable to open the JSON file." << std::endl;
        return;
    }

    // Read JSON content from the file
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();
    std::string jsonContent = buffer.str();

    // Parse and create the JSON document
    rapidjson::Document document;
    document.Parse(jsonContent.c_str());

    // Check if the specified key exists and is an array
    if (document.HasMember(category.c_str()) && document[category.c_str()].IsArray()) {
        const rapidjson::Value& jsonArray = document[category.c_str()];

        // Display the details for each item in the category
        for (rapidjson::SizeType i = 0; i < jsonArray.Size(); i++) {
            const rapidjson::Value& currentItem = jsonArray[i];

            if (currentItem.HasMember("name") && currentItem.HasMember("price") &&
                currentItem.HasMember("taste_balance")) {



                const rapidjson::Value& tasteBalance = currentItem["taste_balance"];
                for (const auto& category : tasteCategories) {
                    if (tasteBalance.HasMember(category.c_str()) && tasteBalance[category.c_str()].IsInt()) {
                        tasteBalanceValues.push_back(tasteBalance[category.c_str()].GetInt());
                    } else {
                        std::cerr << "Error: Invalid or missing fields in item " << i + 1 << std::endl;
                        return;
                    }
                }
            } else {
                std::cerr << "Error: Invalid or missing fields in item " << i + 1 << std::endl;
            }
        }
    } else {
        std::cerr << "Error: The specified key is not a valid array." << std::endl;
    }


    int minError = std::numeric_limits<int>::max();
    int minItemIndex = -1;

    // Display taste balance values and calculate errors
    for (int j = 0; j < 5; j++) {
        std::vector<int> errors(5, 0); // Vector to store errors for each item

        for (int i = 0; i < 5; i++) {
            errors[j] += abs(tasteBalanceValues[i + j * 5] - preference[i]);
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

void taste_balance_advice::generaladvice(){
    
}
int taste_balance_advice::get_generaladvicenum(const std::string& itemname){
    if (itemname == "salads")
    {
        return salads;
    }else if(itemname == "starters"){
        return starters;
    }else if(itemname == "drinks") {
        return drinks;
    }else if(itemname == "main_courses"){
        return maincourses;
    }else if (itemname == "desserts") {
        return desserts;
    }else if (itemname == "appetizers"){
        return appetizers;
    }
    else {
        std::cerr << "invalid item name, try again" << std::endl;
        return 0;
    }
}
void taste_balance_advice::settastebalancenum(int index, int& value) {
    if (index == 1)
    {
        starters = value;
    }else if(index == 2) {
        salads = value;
    }else if(index == 3) {
        maincourses = value;
    }else if(index == 4) {
        drinks = value;
    }else if(index == 5) {
        appetizers = value;
    }else if(index == 6) {
        desserts = value;
    }else {
        std::cerr << "Invalid value, try again" << std::endl;
    }
    
}
taste_balance_advice::taste_balance_advice(){}
taste_balance_advice::~taste_balance_advice(){}