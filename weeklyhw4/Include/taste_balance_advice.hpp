#ifndef TASTE_BALANCE_ADVICE_HPP
#define TASTE_BALANCE_ADVICE_HPP
#include "Menu.hpp"
#include "mainfunction.hpp"
#include <string>
#include "../rapidjson-master/include/rapidjson/document.h"
#include "../rapidjson-master/include/rapidjson/writer.h"
#include "../rapidjson-master/include/rapidjson/stringbuffer.h"
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
    void advice(const std::string& category);
    void set_preference();
    int get_recommendation();
    void general_adivce();
};








#endif //taste_balance_advice.hpp