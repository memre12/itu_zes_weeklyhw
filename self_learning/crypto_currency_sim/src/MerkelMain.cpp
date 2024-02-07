#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "csvReader.hpp"
#include "OrderBook.h"

MerkelMain::MerkelMain()
{


}

void MerkelMain::init()
{
    currentTime = orderbook.getEarliestTime();
    int input;

    wallet.insert_currency("BTC",10);


    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    
    std::cout << "============== " << std::endl;
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for(std::string const p : orderbook.getKnownProducts())
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Products: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderbook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> entriesBid = orderbook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Volume of asks: " << OrderBook::volume(entries) << "$" << std::endl;
        std::cout << "\nBids seen: " << entriesBid.size() << std::endl;
        std::cout << "Max bid: " << OrderBook::getHighPrice(entriesBid) << std::endl;
        std::cout << "Min bid: " << OrderBook::getLowPrice(entriesBid) << std::endl;
        std::cout << "Volume of bids: " << OrderBook::volume(entriesBid) << "$" << std::endl;




    }

}

void MerkelMain::enterAsk()
{
    std::cout << "Mark and offer - enter the amount: product, price, amount, eg, ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = csvReader::tokenise(input, ",");
    if (tokens.size() != 3)
    {
        std::cout << "Invalid input. Try again properly! " << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = csvReader::stringstoOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);

            std::string username = "simuser";
            obe.username = username;

            if (wallet.canFullfill_order(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderbook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "MerkelMain::enterAsk Invalid input! " << '\n';
        }
    }
    std::cout << "You typed " << input << std::endl;
}


void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product, price, amount, eg, ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin,input);
    std::vector<std::string> tokens = csvReader::tokenise(input,",");
    if (tokens.size() != 3)
    {
        std::cout << "Invalid input. Try again properly! " << std::endl;
    }
    else {
        try
        {
            OrderBookEntry obe = csvReader::stringstoOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            ); 
            std::string username = "simuser";
            obe.username = username;     
            if (wallet.canFullfill_order(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderbook.insertOrder(obe);

            }
            else{
                std::cout << "Wallet has insufficient funds. " << std::endl;

            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "MerkelMain::enterBid Invalid input! " << '\n';
        }
    }
    std::cout << "You typed " << input << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << wallet.to_String() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderbook.getKnownProducts())
    {
        std::cout << "Matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderbook.matchasksTobids(p , currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount: " << sale.amount << std::endl;
            if(sale.username == "simuser")
            {
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderbook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line; 
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin,line);
    try
    {
        userOption = std::move(std::stoi(line));
    }
    catch(const std::exception& e)
    {
        std::cerr << "Invalid input!" << e.what() << '\n';
    }
    
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterAsk();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5) 
    {
        printWallet();
    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
    }       
}
