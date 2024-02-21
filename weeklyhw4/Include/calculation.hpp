#pragma once
#ifndef CALCULATION_HPP
#define CALCULATION_HPP

#include <string>
#include <vector>
#include "../rapidjson-master/include/rapidjson/document.h"
#include "../rapidjson-master/include/rapidjson/writer.h"
#include "../rapidjson-master/include/rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <sstream>

class calculation
{
public:
    std::vector<std::string> willaddname;
    std::vector<int> willaddprice;
    std::vector<std::vector<int>> willaddtaste_balance_total;
    void fill_vectors(const std::string& category);
    void show_vectors();
};


#endif /* CALCULATION_HPP */
