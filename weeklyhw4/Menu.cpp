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
#include <limits>
#include <algorithm>
#include <vector>


//class User
User::User(std::string fname, std::string sname) {
    name = std::move(fname); // std::move makes it more effective.
    surname = std::move(sname);
}
void User::set_name(std::string first_name) {
    name = std::move(first_name);
}
void User::set_surname(std::string second_name) {
    surname = std::move(second_name);
}
void User::get_surname() {
    std::cout << "Surname: " << surname << std::endl;
}
void User::get_name() {
    std::cout << "Name: " << name << std::endl;
}
void User::set_gender(std::string gendertype) {
    gendertoaddress = std::move(gendertype);
}
void User::get_gender() {
    std::cout << "Gender:" << " " << gendertoaddress << std::endl;
}

//Menu class
void Menu::addItems(const MenuItem& added_items) {
    chosenitems.push_back(added_items);
}
void Menu::eraseItems(const std::string& itemName) {
    auto it = std::find_if(chosenitems.begin(), chosenitems.end(), [itemName](const MenuItem& item) { return item.get_Foodname() == itemName; });

    if (it != chosenitems.end()) {
        // calculating the index of itemName
        auto index = std::distance(chosenitems.begin(), it);
        std::cout << "Index of " << itemName << ": " << index << std::endl;

        // Remove the element
        chosenitems.erase(it);

        // Print the updated vector
        for (const MenuItem& item : chosenitems) {
            std::cout << item.get_Foodname() << std::endl;
        }
    } else {
        std::cout << "Element not found." << std::endl;
    }
}

void Menu::getChosenItems() {
    std::cout << "****************  MENU DETAILS  ****************\n";
    double overall_sweet = 0.0;
    double overall_sour = 0.0;
    double overall_bitter = 0.0;
    double overall_salty = 0.0;
    double overall_savory = 0.0;
    double total_cost = 0.0;

    for (size_t i = 0; i < chosenitems.size(); i++) {

        std::cout << " Food name: " << chosenitems[i].get_Foodname();
        std::cout << " Food price: " << chosenitems[i].get_Foodprice() << "£" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;

        // Assuming there's at least one taste balance value in the vector
        std::cout << " Sweet balance: " << chosenitems[i].get_tasteBalance()[0];
        std::cout << ", Sour balance: " << chosenitems[i].get_tasteBalance()[1];
        std::cout << ", Bitter balance: " << chosenitems[i].get_tasteBalance()[2];
        std::cout << ", Salty balance: " << chosenitems[i].get_tasteBalance()[3];
        std::cout << ", Savory balance: " << chosenitems[i].get_tasteBalance()[4];

        overall_sweet += chosenitems[i].get_tasteBalance()[0];
        overall_sour += chosenitems[i].get_tasteBalance()[1];
        overall_bitter += chosenitems[i].get_tasteBalance()[2];
        overall_salty += chosenitems[i].get_tasteBalance()[3];
        overall_savory += chosenitems[i].get_tasteBalance()[4];

        total_cost += chosenitems[i].get_Foodprice();

        std::cout << "\n****************************************************" << std::endl;
    }

    // Output overall taste balance
    std::cout << "\nOverall Taste Balance:\n";
    std::cout << "Overall Sweet: " << overall_sweet/chosenitems.size() << std::endl;
    std::cout << "Overall Sour: " << overall_sour/chosenitems.size()  << std::endl;
    std::cout << "Overall Bitter: " << overall_bitter/chosenitems.size()  << std::endl;
    std::cout << "Overall Salty: " << overall_salty/chosenitems.size()  << std::endl;
    std::cout << "Overall Savory: " << overall_savory/chosenitems.size()  << std::endl;

    //total cost
    std::cout << "TOTAL COST : " << total_cost << "£"<< std::endl;

    //goodbye

    std::cout << "\n :)))))) BON APETİT :)))))" << std::endl;
}


//MenuItem class
MenuItem::MenuItem(std::string name, double food_nameobj, std::vector<int> taste_balanceobj) : food_name(name), foodprice(food_nameobj), taste_balance(taste_balanceobj) {
    // Ensure taste balance values are between 0 and 10
    for (int& value : taste_balance) {
        value = std::min(std::max(value, 0), 10);
    }

    // Check if any taste balance values were clamped
    bool clampedValues = std::any_of(taste_balance.begin(), taste_balance.end(), [](int value) {
        return value < 0 || value > 10;
    });

    // Print an error message if necessary
    if (clampedValues) {
        std::cerr << "Error: Taste balance values must be between 0 and 10. Clamping values to the valid range." << std::endl;
    }
}

std::string MenuItem::get_Foodname() const {
    return food_name;
}
void MenuItem::set_Foodname(std::string newFoodname) {
    food_name = std::move(newFoodname);
}
double MenuItem::get_Foodprice() const {
    return foodprice;
}
void MenuItem::set_Foodprice(double newfoodprice) {
    foodprice = std::move(newfoodprice);
}
const std::vector<int>& MenuItem::get_tasteBalance() const {
    return taste_balance;
}
MenuItem::~MenuItem(){}


//Starter class
Starter::Starter(std::string Startername, double Starterfood_price, std::vector<int> Startertaste_balance, std::string settemperature) : MenuItem(Startername,Starterfood_price,Startertaste_balance), temperature(settemperature) {}
void Starter::set_temperature(std::string &attribute) {
    // Convert the string to lowercase
    std::transform(attribute.begin(), attribute.end(), attribute.begin(), [](unsigned char c) { return std::tolower(c); });
    
    if (attribute == "hot") {
        temperature = std::move(attribute);
    } else if (attribute == "cold") {
        temperature = std::move(attribute);
    } else {
        std::cerr << "Error: Invalid input! Input should be 'hot' or 'cold'." << std::endl;
    }
}
std::string Starter::get_temprature() const {
    return temperature;
}
// Implementations for virtual functions
std::string Starter::get_Foodname() const {
    return "Salad: " + MenuItem::get_Foodname();
}
void Starter::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double Starter::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void Starter::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& Starter::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
Starter::~Starter() {}

//Salad class
Salad::Salad(std::string namesalad, double food_pricesalad, std::vector<int> taste_balancesalad, int settoppings): MenuItem(namesalad, food_pricesalad, taste_balancesalad), toppings(settoppings){}
void Salad::set_toppings(int new_toppings) {
    toppings = std::move(new_toppings);
}
int Salad::get_toppings() const {
    return toppings;
}
// Implementations for virtual functions
std::string Salad::get_Foodname() const {
    return "Salad: " + MenuItem::get_Foodname();
}
void Salad::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double Salad::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void Salad::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& Salad::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
Salad::~Salad(){}


//MainCourse class
MainCourse::MainCourse(std::string namemaincourse, double food_pricemaincourse, std::vector<int> taste_balancemaincourse, std::string is_vegetarianmaincourse) : MenuItem(namemaincourse,food_pricemaincourse,taste_balancemaincourse), is_vegetarian(is_vegetarianmaincourse) {}
void MainCourse::ask_vegetarian(std::string &preference) {
    std::transform(preference.begin(), preference.end(), preference.begin(), [](unsigned char c) { return std::tolower(c); });

    if (preference == "vegetarian" || preference == "non-vegetarian") {
        is_vegetarian = std::move(preference);
    } else {
        std::cerr << "Error: Invalid input!" << std::endl;
    }
}
// Implementations for virtual functions
std::string MainCourse::get_Foodname() const {
    return "MainCourse: " + MenuItem::get_Foodname();
}
void MainCourse::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double MainCourse::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void MainCourse::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& MainCourse::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
MainCourse::~MainCourse(){}


//Drink class
Drink::Drink(std::string namedrink, double food_pricedrink, std::vector<int> taste_balancedrink, std::string setextra_alcohol, std::string setextra_carbonated) : MenuItem(namedrink,food_pricedrink,taste_balancedrink), extra_alcohol(setextra_alcohol), extra_carbonated(setextra_carbonated) {}
void Drink::ask_alcohol(std::string &yes_alcohol) {
    std::transform(yes_alcohol.begin(), yes_alcohol.end(), yes_alcohol.begin(), [](unsigned char c) { return std::tolower(c); });

    if (yes_alcohol == "yes") {
        extra_alcohol = std::move(yes_alcohol);
    } else if (yes_alcohol == "no") {
        extra_alcohol = std::move(yes_alcohol);
    } else {
        std::cerr << "Error: Invalid input!" << std::endl;
    }
}
void Drink::ask_carbonated(std::string &yes_carbonated) {
    std::transform(yes_carbonated.begin(), yes_carbonated.end(), yes_carbonated.begin(), [](unsigned char c) { return std::tolower(c); });

    if (yes_carbonated == "yes") {
        extra_carbonated = std::move(yes_carbonated);
    } else if (yes_carbonated == "no") {
        extra_carbonated = std::move(yes_carbonated);
    } else {
        std::cerr << "Error: Invalid input!" << std::endl;
    }
}
// Implementations for virtual functions
std::string Drink::get_Foodname() const {
    return "MainCourse: " + MenuItem::get_Foodname();
}
void Drink::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double Drink::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void Drink::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& Drink::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
Drink::~Drink(){}


// Appetizer class
Appetizer::Appetizer(std::string Appetizername, double Appetizerfood_price, std::vector<int> Appetizertaste_balance,std::string setserve_time) : MenuItem(Appetizername,Appetizerfood_price, Appetizertaste_balance), serve_time(setserve_time) {}
void Appetizer::set_serve_time(std::string &beforeOrAfter) {
    std::transform(beforeOrAfter.begin(), beforeOrAfter.end(), beforeOrAfter.begin(), [](unsigned char c) { return std::tolower(c); });

    if (beforeOrAfter == "before") {
        serve_time = std::move(beforeOrAfter);
    } else if (beforeOrAfter == "after") {
        serve_time = std::move(beforeOrAfter);
    } else {
        std::cerr << "Error: Invalid input!" << std::endl;
    }
}
// Implementations for virtual functions
std::string Appetizer::get_Foodname() const {
    return "MainCourse: " + MenuItem::get_Foodname();
}
void Appetizer::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double Appetizer::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void Appetizer::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& Appetizer::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
Appetizer::~Appetizer() {}

//Dessert class
Dessert::Dessert(std::string Dessertname, double Dessertfood_price, std::vector<int> Desserttaste_balance,std::string setextra_chocolate) : MenuItem(Dessertname,Dessertfood_price,Desserttaste_balance), extra_chocolate(setextra_chocolate) {}
void Dessert::ask_extra_chocolate(std::string &yes_chocolate) {
    std::transform(yes_chocolate.begin(), yes_chocolate.end(), yes_chocolate.begin(), [](unsigned char c) { return std::tolower(c); });
    if (yes_chocolate == "yes") {
        extra_chocolate = std::move(yes_chocolate);
    } else if (yes_chocolate == "no") {
        extra_chocolate = std::move(yes_chocolate);
    } else {
        std::cerr << "Error: Invalid input!" << std::endl;
    }
}
// Implementations for virtual functions
std::string Dessert::get_Foodname() const {
    return "MainCourse: " + MenuItem::get_Foodname();
}
void Dessert::set_Foodname(std::string newFoodname) {
    MenuItem::set_Foodname(newFoodname);
}
double Dessert::get_Foodprice() const {
    return MenuItem::get_Foodprice();
}
void Dessert::set_Foodprice(double newfoodprice) {
    MenuItem::set_Foodprice(newfoodprice);
}
const std::vector<int>& Dessert::get_tasteBalance() const {
    return MenuItem::get_tasteBalance();
}
Dessert::~Dessert() {}

