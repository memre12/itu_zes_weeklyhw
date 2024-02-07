// wallet.h
#ifndef WALLET_H
#define WALLET_H
#include "OrderBookEntry.h"
#include <string>
#include <vector>
#include <map>
#include <csvReader.hpp>

class Wallet {
private:
    std::map<std::string, double> currencies;

public:
    Wallet();
    void insert_currency(std::string type, double amount);
    bool remove_currency(std::string type, double amount);
    void processSale(OrderBookEntry& sale);
    bool canFullfill_order(OrderBookEntry& order);
    bool contains_currency(std::string type, double amount);
    std::string to_String();
};

#endif // WALLET_H
