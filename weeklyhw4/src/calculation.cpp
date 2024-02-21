#include "calculation.hpp" 
#include <string>
#include <vector>
#include <iomanip>
#include <taste_balance_advice.hpp>

void calculation::fill_vectors(const std::string& category){
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
        if (document.HasMember(category.c_str()) && document[category.c_str()].IsArray()) {
            const rapidjson::Value& jsonArray = document[category.c_str()];

            // Display the "name," "price," and "taste_balance" fields of each item
            for (rapidjson::SizeType i = 0; i < jsonArray.Size(); i++) {
                const rapidjson::Value& currentItem = jsonArray[i];

                if (currentItem.HasMember("name") && currentItem["name"].IsString()) {
                    this->willaddname.push_back(currentItem["name"].GetString());
                } else {
                    std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                }

                if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                    this->willaddprice.push_back(currentItem["price"].GetInt());
                } else {
                    std::cerr << "Error: " << i + 1 << " - Invalid or missing 'price' field in item" << std::endl;
                }

                if (currentItem.HasMember("taste_balance") && currentItem["taste_balance"].IsObject()) {
                    const rapidjson::Value& tasteBalanceObj = currentItem["taste_balance"];
                    std::vector<int> tasteBalance;

                    for (const auto& attribute : tasteBalanceObj.GetObject()) {
                        if (attribute.value.IsInt()) {
                            tasteBalance.push_back(attribute.value.GetInt());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing value in 'taste_balance' field" << std::endl;
                        }
                    }

                    this->willaddtaste_balance_total.push_back(tasteBalance);
                } else {
                    std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                }
            }
        } else {
            std::cerr << "Error: The specified key is not a valid array." << std::endl;
        }
}



void calculation::show_vectors() {
    for (int i = 0; i < willaddname.size(); i++) {
        std::cout << std::setw(13) << "Name: " << std::setw(15) << willaddname[i] << std::endl;
        std::cout << std::setw(15) << "Price: " << std::setw(15) << willaddprice[i] << std::endl;
        std::cout << std::setw(15) << "Taste Balance: ";
        for (int j = 0; j < 5; j++) {
            std::cout << std::setw(3) << willaddtaste_balance_total[i][j] << " ";
        }
        std::cout << std::endl << std::endl;
    }
}