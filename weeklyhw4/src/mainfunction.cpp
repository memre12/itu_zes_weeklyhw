#include "Displaymenu.hpp"
#include "Menu.hpp"
#include "mainfunction.hpp"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

void display_tastebalance1(const std::string& category) {
    // Define enum for taste categories
    const std::vector<std::string> tasteCategories = { "sweet", "sour", "bitter", "salty", "savory" };

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

                // Use a vector to store taste balance values
                std::vector<int> tasteBalanceValues;

                const rapidjson::Value& tasteBalance = currentItem["taste_balance"];
                for (const auto& category : tasteCategories) {
                    if (tasteBalance.HasMember(category.c_str()) && tasteBalance[category.c_str()].IsInt()) {
                        tasteBalanceValues.push_back(tasteBalance[category.c_str()].GetInt());
                    } else {
                        std::cerr << "Error: Invalid or missing fields in item " << i + 1 << std::endl;
                        return;
                    }
                }

                // Display taste balance values
                std::cout << "Taste Balance: ";
                for (size_t j = 0; j < tasteCategories.size(); j++) {
                    std::cout << tasteCategories[j] << ": " << tasteBalanceValues[j] << ", ";
                }
                std::cout << std::endl;

                std::cout << "---------------------" << std::endl;
            } else {
                std::cerr << "Error: Invalid or missing fields in item " << i + 1 << std::endl;
            }
        }
    } else {
        std::cerr << "Error: The specified key is not a valid array." << std::endl;
    }
}
void setclient() {
    std::string clientname;
    std::string clientsurname;
    std::string gendertoadress;
    int choice;

    std::cout << "****** Welcome to ZES Restaurant ******" << std::endl;
    std::cout << "Name: " << std::endl;
    getline(std::cin,clientname);
    std::cout << "Surname: " << std::endl;
    getline(std::cin,clientsurname);
    std::cout << "Gender address:\n1-Mr\n2-Mrs" << std::endl;
    std::cin >> choice;
    bool validation = false;
    do
    {
        if (choice==1) {
            validation = false;
            gendertoadress = "Mr";
        }else if(choice==2){
            validation = false;
            gendertoadress = "Mrs";
        }else{
            validation = true;
            std::cerr << "Invalid value, try again" << std::endl;
        }       
    } while (validation);
    
    User client(clientname,clientsurname);
    client.set_gender(gendertoadress);

}

void showmenu() {
    int mainChoice;
    Menu mymenu;

    while (true) {
        std::cout << "What do you want? (Choose any number to see menu details, enter 7 to exit)\n" << "1-starters\n2-Salads\n3-Main Courses\n4-Drinks\n5-Appetizers\n6-Desserts\n";
        

        std::cin >> mainChoice;

        if (mainChoice == 7) {
            std::cout << "Exiting the menu...\n";
            break;  // Exit the while loop if the user enters 7
        }
        int choice;

        std::string category;
        switch (mainChoice) {
            
            case 1:
            category = "starters";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (y/n) (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_starters;
                    client_advice_starters.set_preference();
                    client_advice_starters.advice("starters");
                    choice = std::move(client_advice_starters.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                Starter starterObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1], "hot");

                std::string preference;

                

                std::cout << "What do you want, hot or cold?" << std::endl;
                std::cin >> preference;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (preference == "hot" || preference == "cold")
                {
                    starterObj.set_temperature(preference);
                    std::cout << " Preference is saved." << std::endl;
                }else{
                    std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
                    break;
                }
    

                itemsfromanothervector.push_back(starterObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
                std::cout << "Successfully chosen option " << choice << std::endl;
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5.\n Please try again." << std::endl;
            }
            }
            break;


            case 2:
            category = "salads";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_salads;
                    client_advice_salads.set_preference();
                    client_advice_salads.advice("salads");
                    choice = std::move(client_advice_salads.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                Salad saladObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1], 5);
                
                int nbof_toppings;
                std::cout << "How many topping do you want to? " << std::endl;
                std::cin >> nbof_toppings;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                
                if (nbof_toppings>=0)
                {
                    saladObj.set_toppings(nbof_toppings);
                    saladObj.set_Foodprice(saladObj.get_Foodprice()+nbof_toppings*2.25);
                }else{
                    std::cerr << "This is invalid value, number of toppings should be over 0. \n Please try again." << std::endl;
                }
                
                itemsfromanothervector.push_back(saladObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
                std::cout << "Successfully chosen option " << choice << std::endl;
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5.\n Please try again." << std::endl;
            }
            }
            break;

            case 3:
            category = "main_courses";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_maincourses;
                    client_advice_maincourses.set_preference();
                    client_advice_maincourses.advice("main_courses");
                    choice = std::move(client_advice_maincourses.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                MainCourse maincoursesObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1], "non-vegetarian");
                itemsfromanothervector.push_back(maincoursesObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
                std::cout << "Successfully chosen option " << choice << std::endl;
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5.\n Please try again." << std::endl;
            }
            }
            break;


            case 4:
            category = "drinks";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_drinks;
                    client_advice_drinks.set_preference();
                    client_advice_drinks.advice("drinks");
                    choice = std::move(client_advice_drinks.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                Drink drinkObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1], "yes","no");
                std::string alcohol_preference;
                std::string carbonate_preference;


                std::cout << "Would you like extra alkol?" << std::endl;
                std::cin >> alcohol_preference;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (alcohol_preference == "yes" || alcohol_preference == "no")
                {
                    drinkObj.ask_alcohol(alcohol_preference);
                    std::cout << "Preference is saved." << std::endl;
                    drinkObj.set_Foodprice(drinkObj.get_Foodprice() + 2.5);
                    
                }else if(alcohol_preference == "no") {
                    drinkObj.ask_alcohol(alcohol_preference);
                    std::cout << "Preference is saved" << std::endl;
                }
                else{
                    std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
                }


                std::cout << "Would you like extra carbonated? " << std::endl;
                std::cin >> carbonate_preference;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (carbonate_preference == "yes")
                {
                    drinkObj.ask_carbonated(carbonate_preference);
                    std::cout << "Preference is saved." << std::endl;
                    drinkObj.set_Foodprice(drinkObj.get_Foodprice() + 0.5);
                    std::cout << "Total cost is updated." << drinkObj.get_Foodprice() << std::endl;
                       
                }else if(carbonate_preference == "no"){
                    drinkObj.ask_carbonated(carbonate_preference);
                    std::cout << "Preference is saved." << std::endl;
                }
                else{
                    std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
                }


                itemsfromanothervector.push_back(drinkObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
                std::cout << "Successfully chosen option " << choice << std::endl;
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5." << std::endl;
            }
            }
            break;


            case 5:
            category = "appetizers";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_appetizers;
                    client_advice_appetizers.set_preference();
                    client_advice_appetizers.advice("appetizers");
                    choice = std::move(client_advice_appetizers.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                Appetizer appetizerObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1], "before");
                std::string servetime;
                
                

                std::cout << "When do you want to be served the appetizer, whether before the main course or after the main course? " << std::endl;
                std::cin >> servetime;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (servetime == "after" || servetime == "before")
                {
                    appetizerObj.set_serve_time(servetime);
                    std::cout << " Preference is saved." << std::endl;
                    break;
                }else{
                    std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
                }
                
                itemsfromanothervector.push_back(appetizerObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5." << std::endl;
            }
            }
            break;


            case 6:
            category = "desserts";
            while (true) {
                display_menu(category);
                std::string advice_yn;
                std::cout << "Could you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
                std::cin >> advice_yn;
                if (advice_yn == "y")
                {
                    taste_balance_advice client_advice_desserts;
                    client_advice_desserts.set_preference();
                    client_advice_desserts.advice("drinks");
                    choice = std::move(client_advice_desserts.get_recommendation());
                }else if(advice_yn == "n"){
                    std::cout << "\nWhich one do you want to choose? (to go back to the main menu, input 0)" << std::endl;
                    std::cin >> choice;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else{
                    std::cerr << "This is invalid word, please try again" << std::endl;
                }
                
                

            if (choice >= 1 && choice <= 5) {
                std::vector<std::string> willaddname;
                std::vector<int> willaddprice;
                std::vector<std::vector<int>> willaddtaste_balance_total;
                
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
                            willaddname.push_back(currentItem["name"].GetString());
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'name' field in item" << std::endl;
                        }

                        if (currentItem.HasMember("price") && currentItem["price"].IsInt()) {
                            willaddprice.push_back(currentItem["price"].GetInt());
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

                            willaddtaste_balance_total.push_back(tasteBalance);
                        } else {
                            std::cerr << "Error: " << i + 1 << " - Invalid or missing 'taste_balance' field in item" << std::endl;
                        }
                    }
                } else {
                    std::cerr << "Error: The specified key is not a valid array." << std::endl;
                }

                std::vector<MenuItem> itemsfromanothervector;
                Dessert dessertObj(willaddname[choice-1],willaddprice[choice-1],willaddtaste_balance_total[choice-1],"yes");
                std::string answer;
                std::cout << "Would you like extra extra chocolate?" << std::endl;
                std::cin >> answer;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                if (answer == "yes")
                {
                    dessertObj.ask_extra_chocolate(answer);
                    dessertObj.set_Foodprice(dessertObj.get_Foodprice()+2.25);
                }else if (answer == "no"){
                    dessertObj.ask_extra_chocolate(answer);
                    std::cout << "You did not want to extra chocolate." << std::endl;
                }else {
                    std::cout << "Please input correct word !!!\n Please try again." <<std::endl;
                }
                
                itemsfromanothervector.push_back(dessertObj);

                for (const auto& item : itemsfromanothervector) {
                    mymenu.addItems(item);
                }
                std::cout << "Successfully chosen option " << choice << std::endl;
            } else if (choice == 0) {
            // Exit the loop if choice is 0
            std::cout << "Going back to the main menu." << std::endl;
            break;
            } else {
            std::cout << "Invalid choice. Please choose a number between 0 and 5." << std::endl;
            }
            }
            break;


            default:
            std::cerr << "Invalid input. Choose a number between 1 and 6.\n";
            continue;  // Go back to the main menu
        }


        // Prompt the user to continue or go back to the main menu
        char continueChoice;
        std::cout << "Do you want to continue (y/n)? ";
        std::cin >> continueChoice;

        if (continueChoice != 'y') {
            std::cout << "Exiting the menu...\n";
            break;
        }
    }
    
    std::cout << "Menu details:" << std::endl;
    mymenu.getChosenItems();
    std::cout << "\n" << std::endl;

}