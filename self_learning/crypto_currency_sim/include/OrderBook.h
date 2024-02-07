#pragma once
#include "OrderBookEntry.h"
#include "csvReader.hpp"
#include <string>
#include <vector>

class OrderBook
{
private:
    std::vector<OrderBookEntry> orders;
public:
    // reading a csv file
    OrderBook(std::string filename);
    // return all of products in the dataset
    std::vector<std::string> getKnownProducts();
    // return  vector of orders according to the sent filters
    std::vector<OrderBookEntry> getOrders(OrderBookType, std::string product, std::string timestamp);

    std::string getEarliestTime();

    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchasksTobids(std::string product, std::string timestamp);


    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    
    static double volume(std::vector<OrderBookEntry>& orders);

    static double getLowPrice(std::vector<OrderBookEntry>& orders);

    
    ~OrderBook();
};