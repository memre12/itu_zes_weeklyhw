#ifndef OVERALL_CALC_H
#define OVERALL_CALC_H
#include <vector>
class overall_calc
{
public:
    int recommendation;
    int starters,salads,maincourses,drinks,appetizers,desserts;
    std::vector<int> choice;
    overall_calc() {}
    int get_recommendation();
    void advice(const int& start, const int& end);
};

#endif // OVERALL_CALC_H
