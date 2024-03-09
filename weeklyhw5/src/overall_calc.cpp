#include "overall_calc.h"
#include "mainwindow.h"
void overall_calc::advice(const int& start, const int& end) {
    int minError = std::numeric_limits<int>::max();
    int minItemIndex = -1;

    // Vector to store errors for each item
    std::vector<int> errors(end - start, 0);

    // Display taste balance values and calculate errors
    for (int j = start; j < end; j++) {
        int totalError = 0;
        for (int i = 0; i < 5; i++) {
            totalError += abs(MainWindow::tasete_balancemenu[j][i] - choice[i]);
        }

        // Update errors for the current item
        errors[j - start] = totalError;

        // Check for the minimum error
        if (errors[j - start] < minError) {
            minError = errors[j - start];
            minItemIndex = j + 1;
        }
    }
    recommendation = minItemIndex;
}



int overall_calc::get_recommendation() {
    return recommendation;
}
