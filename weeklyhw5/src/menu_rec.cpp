#include "menu_rec.h"
#include "ui_menu_rec.h"
#include "secondpage.h"
#include <iostream>
#include "QSlider"
#include "QMessageBox"
#include "overall_calc.h"
#include "Menu.h"
#include "mainwindow.h"

menu_rec::menu_rec(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu_rec)
{
    ui->setupUi(this);

}

menu_rec::~menu_rec()
{
    delete ui;
}

void menu_rec::on_sweet_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
    sweet = value;
}


void menu_rec::on_sour_valueChanged(int value)
{
    ui->label_4->setText(QString::number(value));
    sour = value;
}


void menu_rec::on_bitter_valueChanged(int value)
{
    ui->label_5->setText(QString::number(value));
    bitter = value;
}


void menu_rec::on_salty_valueChanged(int value)
{
    ui->label_6->setText(QString::number(value));
    salty = value;
}


void menu_rec::on_savory_valueChanged(int value)
{
    ui->label_7->setText(QString::number(value));
    savory = value;
}

void menu_rec::on_pushButton_clicked()
{
    this->hide();
    secondpage *sec = qobject_cast<secondpage*>(parentWidget());
    if (sec) {
        sec->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}


void menu_rec::on_pushButton_2_clicked()
{

    MainWindow::menuPtr->eraseall();

    // Remove all items from ui->menu_rec_2
    ui->menu_rec_2->clear();
    overall_calc calc;
    calc.choice.push_back(sweet);
    calc.choice.push_back(sour);
    calc.choice.push_back(bitter);
    calc.choice.push_back(salty);
    calc.choice.push_back(savory);
    calc.advice(0,5);
    std::cout << calc.get_recommendation() << std::endl;
    Starter starter(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],"hot");
    calc.recommendation = 0;

    calc.advice(5,10);
    Salad salad(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],0);
    calc.recommendation = 5;

    int vegetarianScore = QMessageBox::question(this, "Question", "Are you vegetarian?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes ? 13 : 10;
    calc.advice(vegetarianScore,15);
    MainCourse maincourse(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],"non-vegetarian");
    calc.recommendation = 10;

    calc.advice(15,20);
    Drink drink(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],"no","no");
    calc.recommendation = 15;

    calc.advice(20,25);
    Appetizer appetizer(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],"after");
    calc.recommendation =20;

    calc.advice(25,30);
    Dessert dessert(MainWindow::namemenu[calc.get_recommendation()],MainWindow::pricemenu[calc.get_recommendation()],MainWindow::tasete_balancemenu[calc.get_recommendation()],"no");
    calc.recommendation = 25;



    //

   // Display a message box with a question and store the user's response
    QMessageBox::StandardButton reply_edit = QMessageBox::question(nullptr, "Edit Menu Properties",
                                                              "Would you like to edit menu properties?",
                                                              QMessageBox::Yes | QMessageBox::No);

    // Check the user's response
    if (reply_edit == QMessageBox::Yes) {
        //User wants to edit menu properties

        //starter
        QMessageBox::StandardButton reply_starter;
        reply_starter = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no)", QMessageBox::Yes | QMessageBox::No);
        QString servingTemperature = (reply_starter == QMessageBox::Yes) ? "hot" : "cold";

        if(servingTemperature == "hot"){
            std::string preference = servingTemperature.toStdString();
            starter.set_temperature(preference);
        }else{
            std::string preference = servingTemperature.toStdString();
            starter.set_temperature(preference);
        }

        //salad

        QMessageBox::StandardButton reply_salad;
        reply_salad = QMessageBox::question(this, "Question", "Do you want to add topic? (2.25$)", QMessageBox::Yes|QMessageBox::No);
        if (reply_salad == QMessageBox::Yes) {
            // User clicked Yes, proceed with adding the salad

            salad.set_Foodprice(salad.get_Foodprice()+2.25);
            MainWindow::menuPtr->addItems(salad);
        } else {
            // User clicked No, do nothing or handle as required
        }

        //main_course

        //no question

        //drinks

        QMessageBox::StandardButton carbonationReply;
        carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated? (0.5$)", QMessageBox::Yes | QMessageBox::No);

        QMessageBox::StandardButton alcoholReply;
        alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink? (2.5$)", QMessageBox::Yes | QMessageBox::No);

        std::string answer = "yes";
        if (carbonationReply == QMessageBox::Yes) {
            drink.set_Foodprice(drink.get_Foodprice()+0.5);
            drink.ask_carbonated(answer);
        }
        std::string answer1 = "yes";

        if (alcoholReply == QMessageBox::Yes) {
            drink.set_Foodprice(drink.get_Foodprice()+2.5);
            drink.ask_alcohol(answer1);
        }

        //appetizer

        QMessageBox::StandardButton reply_appetizer;
        reply_appetizer = QMessageBox::question(this, "Question", "When do you want the appetizer to be served? (if before, click yes/ if after, click no)", QMessageBox::Yes | QMessageBox::No);

        QString servingTime = (reply_appetizer == QMessageBox::Yes) ? "before" : "after";

        if(servingTime == "before"){
            std::string serve_time = servingTime.toStdString();
            appetizer.set_serve_time(serve_time);
        }else{
            std::string serve_time = servingTime.toStdString();
            appetizer.set_serve_time(serve_time);
        }

        // dessert

        QMessageBox::StandardButton reply_dessert;
        reply_dessert = QMessageBox::question(this, "Question", "Do you want extra chocolate? (1.5$)", QMessageBox::Yes | QMessageBox::No);

        double extraCost = (reply_dessert == QMessageBox::Yes) ? 1.5 : 0.0;
        dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);

        MainWindow::menuPtr->addItems(starter);
        MainWindow::menuPtr->addItems(salad);
        MainWindow::menuPtr->addItems(maincourse);
        MainWindow::menuPtr->addItems(drink);
        MainWindow::menuPtr->addItems(appetizer);
        MainWindow::menuPtr->addItems(dessert);
        for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
            QString appinfo = QString::fromStdString(MainWindow::menuPtr->chosenitems[var].get_Foodname()) + " - " + QString::number(MainWindow::menuPtr->chosenitems[var].get_Foodprice()) + " $";
            ui->menu_rec_2->addItem(new QListWidgetItem(appinfo));
        }
        QMessageBox::information(this, "Menu", "Menu is successfully saved");


    } else {
        // User doesn't want to edit menu properties
        MainWindow::menuPtr->addItems(starter);
        MainWindow::menuPtr->addItems(salad);
        MainWindow::menuPtr->addItems(maincourse);
        MainWindow::menuPtr->addItems(drink);
        MainWindow::menuPtr->addItems(appetizer);
        MainWindow::menuPtr->addItems(dessert);
        for (int var = 0; var < MainWindow::menuPtr->chosenitems.size(); ++var) {
            QString appinfo = QString::fromStdString(MainWindow::menuPtr->chosenitems[var].get_Foodname()) + " - " + QString::number(MainWindow::menuPtr->chosenitems[var].get_Foodprice()) + " $";
            ui->menu_rec_2->addItem(new QListWidgetItem(appinfo));
        }
        QMessageBox::information(this, "Menu", "Menu is successfully saved");

    }
}


void menu_rec::on_pushButton_3_clicked()
{
    // Remove items from MainWindow::menuPtr
    MainWindow::menuPtr->eraseall();

    // Remove all items from ui->menu_rec_2
    ui->menu_rec_2->clear();

    QMessageBox::information(this, "Menu", "Menu is successfully deleted");

}

