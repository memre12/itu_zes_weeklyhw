// Displaymenu.hpp
#ifndef DISPLAYMENU_HPP
#define DISPLAYMENU_HPP

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
#include "taste_balance_advice.hpp"

void display_menu(const std::string& arrayName);
void display_price(const std::string& arrayPrice);


#endif // DISPLAYMENU_HPP
