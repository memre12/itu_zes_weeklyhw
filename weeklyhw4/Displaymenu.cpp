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
