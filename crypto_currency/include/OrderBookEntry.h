#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown, sale, asksale, bisale};

class OrderBookEntry
{
    public:

        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType,
                        std::string _username = "dataset");
        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);
        static bool compareBypPriceAscending(OrderBookEntry& e1, OrderBookEntry& e2);
        static bool compareByPriceDescending(OrderBookEntry& e1, OrderBookEntry& e2);


    
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username = "dataset";
};
