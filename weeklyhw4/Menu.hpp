// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
class MenuItem; //Forward declaration



class User {
    private:
    std::string name;
    std::string surname;
    std::string gendertoaddress;
    public:
    User(std::string fname, std::string sname);
    void set_name(std::string first_name);
    void get_name();
    void set_surname(std::string second_name);
    void get_surname();
    void set_gender(std::string gendertype);
    void get_gender();
};


class Menu {
    private:
    std::vector<MenuItem> chosenitems;
    int totalcost;
    public:
    void addItems(const MenuItem& added_items);
    void eraseItems(const std::string& K);
    void getChosenItems();

};

class MenuItem {
    private:
    std::string food_name;
    double foodprice;
    std::vector<int> taste_balance {1,2,3,4,5};
    public:
    MenuItem(std::string name, double food_nameobj, std::vector<int> taste_balanceobj);
    virtual ~MenuItem();
    virtual std::string get_Foodname() const;
    virtual void set_Foodname(std::string newFoodname);
    virtual double get_Foodprice() const;
    virtual void set_Foodprice(double newfoodprice);
    virtual const std::vector<int>& get_tasteBalance() const;
};

class Starter : public MenuItem {
    private:
    std::string temperature;
    public:
    Starter(std::string Startername, double Starterfood_price, std::vector<int> Startertaste_balance, std::string settemperature);
    virtual ~Starter();
    void set_temperature(std::string &attribute);
    std::string get_temprature() const;
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;
};

class Salad : public MenuItem {
    private:
    int toppings;
    public:
    Salad(std::string namesalad, double food_pricesalad, std::vector<int> taste_balancesalad, int settoppings);
    virtual ~Salad();
    void set_toppings(int new_toppings);
    int get_toppings() const;
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;
};

class MainCourse : public MenuItem {
    private:
    std::string is_vegetarian;
    public:
    MainCourse(std::string namemaincourse, double food_pricemaincourse, std::vector<int> taste_balancemaincourse, std::string is_vegetarianmaincourse);
    virtual ~MainCourse();
    void ask_vegetarian(std::string &preference);
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;
};

class Drink : public MenuItem {
    private:
    std::string extra_alcohol;
    std::string extra_carbonated;
    public:
    Drink(std::string namedrink, double food_pricedrink, std::vector<int> taste_balancedrink, std::string setextra_alcohol, std::string setextra_carbonated);
    virtual ~Drink();
    void ask_carbonated(std::string &yes_carbonated);
    void ask_alcohol(std::string &yes_alcohol);
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;

};

class Appetizer : public MenuItem {
    private:
    std::string serve_time;
    public:
    Appetizer(std::string Appetizername, double Appetizerfood_price, std::vector<int> Appetizertaste_balance,std::string setserve_time);
    virtual ~Appetizer();
    void set_serve_time(std::string &beforeOrAfter);
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;
};

class Dessert : public MenuItem {
    private:
    std::string extra_chocolate;
    public:
    Dessert(std::string Dessertname, double Dessertfood_price, std::vector<int> Desserttaste_balance,std::string setextra_chocolate);
    virtual ~Dessert();
    void ask_extra_chocolate(std::string &yes_chocolate);
    std::string get_Foodname() const override;
    void set_Foodname(std::string newFoodname) override;
    double get_Foodprice() const override;
    void set_Foodprice(double newfoodprice) override;
    const std::vector<int>& get_tasteBalance() const override;
};
#endif // MENU_HPP
