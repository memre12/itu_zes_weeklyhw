#include "Displaymenu.hpp"
#include "Menu.hpp"
#include "mainfunction.hpp"
#include <string>
#include "rapidjson-master/include/rapidjson/document.h"
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 


/*#include <vector>

enum TasteType {
    Sweet,
    Sour,
    Bitter,
    Salty,
    Savory
};

std::vector<int> convertTasteBalanceEnumToVector() {
    std::vector<int> taste_balance;
    taste_balance.push_back(static_cast<int>(Sweet));
    taste_balance.push_back(static_cast<int>(Sour));
    taste_balance.push_back(static_cast<int>(Bitter));
    taste_balance.push_back(static_cast<int>(Salty));
    taste_balance.push_back(static_cast<int>(Savory));

    return taste_balance;
}

// Usage
std::vector<int> taste_balance = convertTasteBalanceEnumToVector();
*/


//JSON FILE application
/**/
void display_menu(const std::string& arrayName) {
    // Read the JSON file
    std::ifstream ifs("menu.json");
    if (!ifs.is_open()) {
        std::cerr << "Unable to open the JSON file." << std::endl;
        return;
    }

    // Read JSON content from the file
    std::string jsonContent((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    ifs.close();

    // Parse and create the JSON document
    rapidjson::Document document;
    document.Parse(jsonContent.c_str());

    // Check if the specified key exists and is an array
    if (document.HasMember(arrayName.c_str()) && document[arrayName.c_str()].IsArray()) {
        const rapidjson::Value& jsonArray = document[arrayName.c_str()];
        
        // Display the "name" field of each item
        for (rapidjson::SizeType i = 0; i < jsonArray.Size(); i++) {
            const rapidjson::Value& currentItem = jsonArray[i];
            
            if (currentItem.HasMember("name") && currentItem["name"].IsString()) {
                std::cout << arrayName << " " << i + 1 << ": " << currentItem["name"].GetString() << std::endl;
            } else {
                std::cerr << "Error: " << i + 1 << " " << std::endl;
            }
        }
    } else {
        std::cerr << "Error: The specified key is not a valid array." << std::endl;
    }
}

void display_price(const std::string& arrayPrice) {
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
    if (document.HasMember(arrayPrice.c_str()) && document[arrayPrice.c_str()].IsArray()) {
        const rapidjson::Value& jsonArray = document[arrayPrice.c_str()];

        // Display the "price" field of each item
        for (rapidjson::SizeType i = 0; i < jsonArray.Size(); i++) {
            const rapidjson::Value& currentItem = jsonArray[i];

            if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                std::cout << arrayPrice << " " << i + 1 << ": $" << currentItem["price"].GetInt() << std::endl;
            } else {
                std::cerr << "Error: Invalid or missing 'price' field in item " << i + 1 << std::endl;
            }
        }
    } else {
        std::cerr << "Error: The specified key is not a valid array." << std::endl;
    }
}

/*
void display_tastebalance(const std::string& category) {
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

                std::cout << "Name: " << currentItem["name"].GetString() << std::endl;
                std::cout << "Price: $" << currentItem["price"].GetInt() << std::endl;

                const rapidjson::Value& tasteBalance = currentItem["taste_balance"];
                std::cout << "Taste Balance: ";
                std::cout << "Sweet: " << tasteBalance["sweet"].GetInt() << ", ";
                std::cout << "Sour: " << tasteBalance["sour"].GetInt() << ", ";
                std::cout << "Bitter: " << tasteBalance["bitter"].GetInt() << ", ";
                std::cout << "Salty: " << tasteBalance["salty"].GetInt() << ", ";
                std::cout << "Savory: " << tasteBalance["savory"].GetInt() << std::endl;

                std::cout << "---------------------" << std::endl;
            } else {
                std::cerr << "Error: Invalid or missing fields in item " << i + 1 << std::endl;
            }
        }
    } else {
        std::cerr << "Error: The specified key is not a valid array." << std::endl;
    }
}
*/
