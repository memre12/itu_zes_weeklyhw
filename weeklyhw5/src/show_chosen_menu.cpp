#include "show_chosen_menu.h"
#include "ui_show_chosen_menu.h"
#include "mainwindow.h"
#include "secondpage.h"
#include <iostream>

show_chosen_menu::show_chosen_menu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::show_chosen_menu)
{
    ui->setupUi(this);
    // Display chosen items in the list widget
    for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
        QString appinfo = QString::number(var + 1) + "- " + QString::fromStdString(MainWindow::menuPtr->chosenitems[var].get_Foodname()) + " - " + QString::number(MainWindow::menuPtr->chosenitems[var].get_Foodprice()) + " $";
        ui->chosen_menu->addItem(new QListWidgetItem(appinfo));
    }

    // Calculate total cost
    double total = 0;
    for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
        total += MainWindow::menuPtr->chosenitems[var].get_Foodprice(); // Accumulate total cost
    }

    // Display total cost in another list widget
    QString total_cost = QString::number(total) + " $";
    ui->aaaa->addItem(new QListWidgetItem(total_cost));

}

show_chosen_menu::~show_chosen_menu()
{
    delete ui;
}

void show_chosen_menu::on_pushButton_clicked()
{
    this->hide();
    secondpage *sec = qobject_cast<secondpage*>(parentWidget());
    if (sec) {
        sec->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}

void show_chosen_menu::on_spinBox_valueChanged(int arg1)
{
    auto is_numeric = [](const std::string &str) -> bool {
        if (str.empty()) // Empty string is not considered numeric
            return false;

        size_t start = 0;

        // Check for negative number
        if (str[0] == '-')
            start = 1;

        // Check each character to be a digit
        for (size_t i = start; i < str.size(); ++i) {
            if (!std::isdigit(str[i])) // If any character is not a digit, return false
                return false;
        }
        return true; // All characters are digits, return true
    };

    QString text = QString::number(arg1); // Convert arg1 to QString
    if (is_numeric(text.toStdString())) {
        // If value is numeric, assign it to 'n'
        n = arg1;
    } else {
        // If value is not numeric, assign 0 to 'n'
        n = 0;
    }
}

void show_chosen_menu::on_pushButton_2_clicked()
{
    int indexToRemove = n - 1; // Adjusting the index to match user input
    if (MainWindow::menuPtr != nullptr && indexToRemove >= 0 && indexToRemove < MainWindow::menuPtr->chosenitems.size()) {
        // Remove the element at the adjusted index from the vector
        MainWindow::menuPtr->chosenitems.erase(MainWindow::menuPtr->chosenitems.begin() + indexToRemove);

        std::cout << "Removed the " << n << "th element from the vector." << std::endl;
    } else {
        std::cerr << "Error: Unable to remove the " << n << "th element from the vector. Invalid index or element does not exist." << std::endl;
    }


    // Clear the items displayed in the chosen_menu list widget
    ui->chosen_menu->clear();

    // Display chosen items in the list widget
    for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
        QString appinfo = QString::number(var + 1) + "- " + QString::fromStdString(MainWindow::menuPtr->chosenitems[var].get_Foodname()) + " - " + QString::number(MainWindow::menuPtr->chosenitems[var].get_Foodprice()) + " $";
        ui->chosen_menu->addItem(new QListWidgetItem(appinfo));
    }

    ui->aaaa->clear();
    // Calculate total cost
    double total = 0;
    for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
        total += MainWindow::menuPtr->chosenitems[var].get_Foodprice(); // Accumulate total cost
    }

    // Display total cost in another list widget
    QString total_cost = QString::number(total) + " $";
    ui->aaaa->addItem(new QListWidgetItem(total_cost));
}


