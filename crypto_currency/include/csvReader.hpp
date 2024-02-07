#pragma once
#ifndef CSVREADER_HPP
#define CSVREADER_HPP
#include "OrderBookEntry.h"
#include <vector>
#include <string>


class csvReader
{
public:
    csvReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenise(std::string csvLine, const std::string& separator);
    static OrderBookEntry stringstoOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType);

    ~csvReader();
private:
    static OrderBookEntry stringstoOBE(std::vector<std::string> strings);
};




#endif // CSVREADER_HPP