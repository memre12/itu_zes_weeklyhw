#include "OrderBookEntry.h"
#include <iostream>

OrderBookEntry::OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType,
                        std::string _username)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType),
  username(_username)
{
    
}
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
  if (s == "ask")
  {
    return OrderBookType::ask;
  }else if (s == "bid")
  {
    return OrderBookType::bid;
  }else{
    std::cerr << "Invalid word, please try again properly." << std::endl;
    return OrderBookType::unknown;
  }  
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.timestamp > e2.timestamp;
}

bool OrderBookEntry::compareBypPriceAscending(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDescending(OrderBookEntry& e1, OrderBookEntry& e2)
{
  return e1.price > e2.price;
}