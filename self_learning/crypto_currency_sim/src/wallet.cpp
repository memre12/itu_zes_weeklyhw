// wallet.cpp
#include "wallet.h"
#include <iostream>
#include <csvReader.hpp>

Wallet::Wallet() {
    // Constructor implementation if needed
}

void Wallet::insert_currency(std::string type, double amount) {
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type)== 0)
    {
        balance = 0;
    }
    else{
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::contains_currency(std::string type, double amount) {
    if (currencies.count(type)== 0) 
        return false;
    else
        return currencies[type] >= amount;
    return currencies[type] >= amount;
}

std::string Wallet::to_String() {
    std::string result;
    for (const auto& currency : currencies) {
        result += currency.first + ": " + std::to_string(currency.second) + "\n";
    }
    return result;
}

bool Wallet::remove_currency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type)== 0)
    {
        std::cout << "There is no currency for " << type << std::endl;
        return false;
    }
    else{
        if(contains_currency(type,amount))
        {
            std::cout << "Removing " << type << ": " << amount << std::endl;
            currencies[type] -= amount;
            return true;
        }else{
            return false;
        }
    }
}

bool Wallet::canFullfill_order(OrderBookEntry& order)
{
    std::vector<std::string> currs = csvReader::tokenise(order.product, "/");

    if(order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFullfill_order " << currency << " : " << amount << std::endl;
        return contains_currency(currency, amount);
    }
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFullfill_order " << currency << " : " << amount << std::endl;
        return contains_currency(currency, amount);
    }
    
    return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{  
    std::vector<std::string> currs = csvReader::tokenise(sale.product, "/");

    double incomingAmount, outgoingAmount;
    std::string incomingCurrency, outgoingCurrency;

    if (sale.orderType == OrderBookType::asksale)
    {
        outgoingAmount = sale.amount;
        outgoingCurrency = currs[0];
        incomingAmount = sale.amount * sale.price;
        incomingCurrency = currs[1];
    }
    else if (sale.orderType == OrderBookType::bisale)
    {
        incomingAmount = sale.amount;
        incomingCurrency = currs[0];
        outgoingAmount = sale.amount * sale.price;
        outgoingCurrency = currs[1];
    }
    else
    {
        // Handle other sale types if necessary
        return;
    }

    currencies[incomingCurrency] += incomingAmount;
    currencies[outgoingCurrency] -= outgoingAmount;
}
