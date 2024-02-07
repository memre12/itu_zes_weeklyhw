#include "csvReader.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

csvReader::csvReader(){}
csvReader::~csvReader(){}

std::vector<OrderBookEntry> csvReader::readCSV(std::string csvFilename) {
    std::vector<OrderBookEntry> entries;
    std::fstream csvFile{csvFilename};
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringstoOBE(tokenise(line, ","));
                entries.push_back(obe);
            } catch (const std::exception& e) {
                std::cerr << "Error processing data: " << e.what() << std::endl;
            }
        }
        csvFile.close();  // Close the file after reading
    } else {
        std::cerr << "csvReader::readCSV could not open file: " << csvFilename << std::endl;
    }

    std::cout << "csvReader::readCSV read " << entries.size() << " entries" << std::endl;

    return entries;  // Return the populated entries vector
}


std::vector<std::string> csvReader::tokenise(std::string csvLine, const std::string& separator){
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        start = csvLine.find_first_not_of(separator, start);
        if (start == std::string::npos) break; // exit if no more non-separator characters found

        end = csvLine.find_first_of(separator, start);
        if (end == std::string::npos) // if no more separators found
            end = csvLine.length();

        std::string token = csvLine.substr(start, end - start);
        tokens.push_back(token);

        start = end + separator.length();
    } while (end < csvLine.length());
    
    return tokens;
}

OrderBookEntry csvReader::stringstoOBE(std::vector<std::string> tokens) {
    if (tokens.size() != 5) {
        std::cout << "Bad line" << std::endl;
        throw std::exception{};
    }

    try {
        double price = std::stod(tokens[3]);
        double amount = std::stod(tokens[4]);

        // Use the obtained price and amount to initialize OrderBookEntry
        OrderBookEntry obe{price,
                            amount,
                            tokens[0],
                            tokens[1],
                            OrderBookEntry::stringToOrderBookType(tokens[2])};

        return obe;
    } catch (const std::exception& e) {
        std::cout << "Error processing line: " << e.what() << '\n';
        // Handle the error or continue processing other lines
        throw;  // Optionally rethrow the exception if you want to stop processing the current file
    }
}

OrderBookEntry csvReader::stringstoOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch(const std::exception& e)
    {
        std::cerr << "csvReader::stringstoOBE Error converting strings to double values. Price: " << priceString << ", Amount: " << amountString << ". Error: " << e.what() << '\n';
    }
    OrderBookEntry obe{price,
                    amount,
                    timestamp,
                    product,
                    orderType};
    
    return obe;
    
}