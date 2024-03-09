#ifndef READJSON_H
#define READJSON_H
#include <vector>
#include <string>


class readjson
{
public:
    std::vector<std::string> willaddname;
    std::vector<double> willaddprice;
    std::vector<std::vector<int>> willaddtaste_balance_total;
    readjson() {}
    void fill_items();
};
#endif // READJSON_H
