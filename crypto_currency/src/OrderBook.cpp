#include "OrderBook.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "csvReader.hpp"
#include <string>
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = csvReader::readCSV(filename); // you can use static function with this description.
}
// return all of products in the dataset
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> productMap;  
    for (OrderBookEntry& e : orders)
    {
        productMap[e.product] = true;
    }
    for (auto const& e : productMap)
    {
        products.push_back(e.first);
    }
    return products;
}

// return  vector of orders according to the sent filters
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

double OrderBook::volume(std::vector<OrderBookEntry>& orders)
{
    double total = 0.0;

    for (const OrderBookEntry& e : orders)
    {
        total += e.amount*e.price;
    }   

    return total;
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;  // Initialize max with the first element's price
    for (const OrderBookEntry& e : orders)
    {
        if (e.price > max) {
            max = e.price;
        }
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;  // Initialize max with the first element's price
    for (const OrderBookEntry& e : orders)
    {
        if (e.price < min) {
            min = e.price;
        }
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}



std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string nexttimestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            nexttimestamp = e.timestamp;
            break;
        }
    }
    if (nexttimestamp == "")
    {
        nexttimestamp = orders[0].timestamp;
    }

    return nexttimestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchasksTobids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareBypPriceAscending);
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceDescending);

    for (OrderBookEntry& ask : asks )
    {
        for (OrderBookEntry& bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price,0, timestamp, product, OrderBookType::asksale};

                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bisale;
                }if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }
                
                if(bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }

                if (ask.amount > bid.amount && bid.amount > 0)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }

            }
        }
    }
    return sales;
}

OrderBook::~OrderBook(){}