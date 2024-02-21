#include "Displaymenu.hpp"
#include "Menu.hpp"
#include "mainfunction.hpp"
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "calculation.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

void setclient() {
    std::string clientname;
    std::string clientsurname;
    std::string gendertoadress;
    std::string choice;

    std::cout << "****** Welcome to ZES Restaurant ******" << std::endl;

    std::cout << "Name: ";
    std::getline(std::cin, clientname);

    std::cout << "Surname: ";
    std::getline(std::cin, clientsurname);

    while (true) {
        std::cout << "Gender address:\n1-Mr\n2-Mrs: ";
        std::getline(std::cin, choice);

        try {
            // Attempt to convert the input to an integer
            int genderChoice = std::stoi(choice);

            if (genderChoice == 1) {
                gendertoadress = "Mr";
                break;
            } else if (genderChoice == 2) {
                gendertoadress = "Mrs";
                break;
            } else {
                std::cerr << "Invalid input. Please enter 1 or 2." << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            // Handle the case where the input is not a valid integer
            std::cerr << "Invalid input. Please enter a number." << std::endl;
        }
    }

    User client(clientname, clientsurname);
    client.set_gender(gendertoadress);
}


void showmenu() {
    int mainChoice;
    std::string mainChoiceString;
    Menu mymenu;
    std::string choiceString;
    int choice;
    std::string category;

    while (true) {
        
        while (true) {
            std::cout << "What do you want? (Choose number to see menu details))\n"
                    << "1-Starters\n2-Salads\n3-Main Courses\n4-Drinks\n5-Appetizers\n6-Desserts\n7-Show current menu\n8-Menu advice\n9-Exit the menu\n";
            std::cin >> mainChoiceString;

            try {
                // Attempt to convert the input to an integer
                mainChoice = std::stoi(mainChoiceString);

                if (mainChoice >= 1 && mainChoice <= 9) {
                    break;
                } else {
                    std::cerr << "Invalid input. Please enter a number between 1 and 8." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                // Handle the case where the input is not a valid integer
                std::cerr << "Invalid input. Please enter a number." << std::endl;
            }

            // Clear the input buffer to handle any remaining characters
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (mainChoice) {
            case 1:
            category = "starters";
            while (true) {

                calculation startercalculation;

                startercalculation.fill_vectors(category);

                startercalculation.show_vectors();
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (y/n) (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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
                Starter starterObj(startercalculation.willaddname[choice-1],startercalculation.willaddprice[choice-1],startercalculation.willaddtaste_balance_total[choice-1], "hot");
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
                mymenu.addItems(starterObj);
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
                calculation saladcalculation;
                
                saladcalculation.fill_vectors(category);

                saladcalculation.show_vectors();
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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

                Salad saladObj(saladcalculation.willaddname[choice-1],saladcalculation.willaddprice[choice-1],saladcalculation.willaddtaste_balance_total[choice-1], 5);
                
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
                mymenu.addItems(saladObj);
                
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
                calculation maincoursecalculation;

                maincoursecalculation.fill_vectors(category);  

                maincoursecalculation.show_vectors();
                
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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
                              
                MainCourse maincoursesObj(maincoursecalculation.willaddname[choice-1],maincoursecalculation.willaddprice[choice-1],maincoursecalculation.willaddtaste_balance_total[choice-1], "non-vegetarian");
                mymenu.addItems(maincoursesObj);
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
                calculation drinkscalculation;

                drinkscalculation.fill_vectors(category);
                drinkscalculation.show_vectors();
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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
                
                Drink drinkObj(drinkscalculation.willaddname[choice-1],drinkscalculation.willaddprice[choice-1],drinkscalculation.willaddtaste_balance_total[choice-1], "yes","no");
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
                mymenu.addItems(drinkObj);              
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
                calculation appetizercalculation;
                appetizercalculation.fill_vectors(category);

                appetizercalculation.show_vectors();                
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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
                Appetizer appetizerObj(appetizercalculation.willaddname[choice-1],appetizercalculation.willaddprice[choice-1],appetizercalculation.willaddtaste_balance_total[choice-1], "before");
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
                mymenu.addItems(appetizerObj);
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
                calculation dessertcalculation;
                dessertcalculation.fill_vectors(category);

                dessertcalculation.show_vectors();
                std::string advice_yn;
                std::cout << "Do you want to get an advice? (to go back to the main menu, input 'n' and then input 0.)" << std::endl;
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
                Dessert dessertObj(dessertcalculation.willaddname[choice-1],dessertcalculation.willaddprice[choice-1],dessertcalculation.willaddtaste_balance_total[choice-1],"yes");
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
                mymenu.addItems(dessertObj);
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

            case 7:
            mymenu.getChosenItems();
            std::cout << "\n" << std::endl;
            std::cout << "Do you want to remove any item from the menu? (y/n)" << std::endl;
            std::cin >> choiceString;
            while (true)
            {
                if (choiceString == "y") {
                    int removeChoice;
                    std::cout << "Which item do you want to remove? (Choose number to remove item)" << std::endl;
                    std::cin >> removeChoice;
                    removeChoice -= 1;
                    mymenu.eraseItems(removeChoice);
                    std::cout << "Item removed from the menu." << std::endl;
                    break;
                } else if (choiceString == "n") {
                    std::cout << "No item removed from the menu." << std::endl;
                    break;
                } else {
                    std::cerr << "Invalid input. Please enter 'y' or 'n'." << std::endl;
                }
            }
            
            
            break;

            case 8: {
            std::cout << "Menu advice" << std::endl; // general advice
            // create an object of the class calculation
            calculation general_advice;
            general_advice.fill_vectors("desserts");
            // create an object of the class taste_balance_advice
            taste_balance_advice _general_advice;
            _general_advice.set_preference();
            //dessert advice
            _general_advice.advice("desserts");
            choice = std::move(_general_advice.get_recommendation());
            Dessert dessert_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], "yes");
            std::string answer;
            std::cout << "Would you like extra extra chocolate in your advised dessert?" << std::endl;
            std::cin >> answer;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (answer == "yes") {
                dessert_advice.ask_extra_chocolate(answer);
                dessert_advice.set_Foodprice(dessert_advice.get_Foodprice() + 2.25);
            } else if (answer == "no") {
                dessert_advice.ask_extra_chocolate(answer);
                std::cout << "You did not want extra chocolate." << std::endl;
            } else {
                std::cout << "Please input correct word !!!\n Please try again." << std::endl;
            }
            mymenu.addItems(dessert_advice);
            general_advice.willaddname.clear();
            general_advice.willaddprice.clear();
            general_advice.willaddtaste_balance_total.clear();
            //salads advice
            general_advice.fill_vectors("salads");
            _general_advice.advice("salads");
            choice = std::move(_general_advice.get_recommendation());
            Salad salad_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], 5);
            int nbof_toppings;
            std::cout << "How many topping do you want to in your advised salad? " << std::endl;
            std::cin >> nbof_toppings;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (nbof_toppings >= 0) {
                salad_advice.set_toppings(nbof_toppings);
                salad_advice.set_Foodprice(salad_advice.get_Foodprice() + nbof_toppings * 2.25);
            } else {
                std::cerr << "This is invalid value, number of toppings should be over 0. \n Please try again." << std::endl;
            }
            mymenu.addItems(salad_advice);
            general_advice.willaddname.clear();
            general_advice.willaddprice.clear();
            general_advice.willaddtaste_balance_total.clear();
            //drinks advice
            general_advice.fill_vectors("drinks");
            _general_advice.advice("drinks");
            choice = std::move(_general_advice.get_recommendation());
            Drink drink_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], "yes", "no");
            std::string alcohol_preference;
            std::string carbonate_preference;
            std::cout << "Would you like extra alkol in your advised drink?" << std::endl;
            std::cin >> alcohol_preference;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (alcohol_preference == "yes" || alcohol_preference == "no") {
                drink_advice.ask_alcohol(alcohol_preference);
                std::cout << "Preference is saved." << std::endl;
                drink_advice.set_Foodprice(drink_advice.get_Foodprice() + 2.5);
            } else if (alcohol_preference == "no") {
                drink_advice.ask_alcohol(alcohol_preference);
                std::cout << "Preference is saved" << std::endl;
            } else {
                std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
            }
            std::cout << "Would you like extra carbonated in your advised drink? " << std::endl;
            std::cin >> carbonate_preference;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (carbonate_preference == "yes") {
                drink_advice.ask_carbonated(carbonate_preference);
                std::cout << "Preference is saved." << std::endl;
                drink_advice.set_Foodprice(drink_advice.get_Foodprice() + 0.5);
                std::cout << "Total cost is updated." << drink_advice.get_Foodprice() << std::endl;

            } else if (carbonate_preference == "no") {
                drink_advice.ask_carbonated(carbonate_preference);
                std::cout << "Preference is saved." << std::endl;
            } else {
                std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
            }
            mymenu.addItems(drink_advice);
            general_advice.willaddname.clear();
            general_advice.willaddprice.clear();
            general_advice.willaddtaste_balance_total.clear();
            //appetizers advice
            general_advice.fill_vectors("appetizers");
            _general_advice.advice("appetizers");
            choice = std::move(_general_advice.get_recommendation());
            Appetizer appetizer_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], "before");
            std::string servetime;
            std::cout << "When do you want to be served the appetizer, whether before the main course or after the main course? " << std::endl;
            std::cin >> servetime;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (servetime == "after" || servetime == "before") {
                appetizer_advice.set_serve_time(servetime);
                std::cout << " Preference is saved." << std::endl;
            } else {
                std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
            }
            mymenu.addItems(appetizer_advice);
            general_advice.willaddname.clear();
            general_advice.willaddprice.clear();
            general_advice.willaddtaste_balance_total.clear();
            //main courses advice
            general_advice.fill_vectors("main_courses");
            _general_advice.advice("main_courses");
            choice = std::move(_general_advice.get_recommendation());
            MainCourse maincourses_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], "non-vegetarian");
            mymenu.addItems(maincourses_advice);
            general_advice.willaddname.clear();
            general_advice.willaddprice.clear();
            general_advice.willaddtaste_balance_total.clear();
            //starters advice
            general_advice.fill_vectors("starters");
            _general_advice.advice("starters");
            choice = std::move(_general_advice.get_recommendation());
            Starter starter_advice(general_advice.willaddname[choice-1], general_advice.willaddprice[choice-1], general_advice.willaddtaste_balance_total[choice-1], "hot");
            std::string preference;
            std::cout << "What do you want, hot or cold?" << std::endl;
            std::cin >> preference;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (preference == "hot" || preference == "cold") {
                starter_advice.set_temperature(preference);
                std::cout << " Preference is saved." << std::endl;
            } else {
                std::cerr << "Please input correct word !!!\n Please try again." << std::endl;
            }
            mymenu.addItems(starter_advice);
            break;
        }


            case 9:
            std::cout << "Exiting the menu..." << std::endl;
            break;
            default:
            std::cerr << "Invalid input. Choose a number between 1 and 8.\n";
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