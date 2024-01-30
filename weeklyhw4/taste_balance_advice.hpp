#ifndef TASTE_BALANCE_ADVICE_HPP
#define TASTE_BALANCE_ADVICE_HPP
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


class taste_balance_advice
{
private:
    int recommendation;
    int starters,salads,maincourses,drinks,appetizers,desserts;
    std::vector<int> choice;
public:
    taste_balance_advice();
    void advice(const std::string& category);
    void set_preference();
    void settastebalancenum(int index, int& value);
    void generaladvice();
    int get_generaladvicenum(const std::string& itemname);
    int get_recommendation();
    ~taste_balance_advice();
};








#endif //taste_balance_advice.hpp