#include "drinks.h"
#include "ui_drinks.h"
#include "menu_titles.h"
#include "Menu.h"
#include "mainwindow.h"
#include "QMessageBox"
drinks::drinks(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::drinks)
{
    ui->setupUi(this);
    for (int var = 15; var < 20; ++var) {
        QString saladInfo = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
        ui->drinks_list->addItem(new QListWidgetItem(saladInfo));
        if(var<19){
            ui->drinks_list->addItem(new QListWidgetItem("\n"));
        }
    }
}

drinks::~drinks()
{
    delete ui;
}

void drinks::on_pushButton_clicked()
{
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}


void drinks::on_checkBox_clicked()
{
    QMessageBox::StandardButton carbonationReply;
    carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated?", QMessageBox::Yes | QMessageBox::No);

    QMessageBox::StandardButton alcoholReply;
    alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink?", QMessageBox::Yes | QMessageBox::No);

    Drink drinkObj(MainWindow::namemenu[15], MainWindow::pricemenu[15], MainWindow::tasete_balancemenu[15], "no","no");
    std::string answer = "yes";
    if (carbonationReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+0.5);
        drinkObj.ask_carbonated(answer);
    }

    if (alcoholReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+2.5);
        drinkObj.ask_alcohol(answer);
    }

    MainWindow::menuPtr->addItems(drinkObj);
}


void drinks::on_checkBox_2_clicked()
{
    QMessageBox::StandardButton carbonationReply;
    carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated?", QMessageBox::Yes | QMessageBox::No);

    QMessageBox::StandardButton alcoholReply;
    alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink?", QMessageBox::Yes | QMessageBox::No);

    Drink drinkObj(MainWindow::namemenu[16], MainWindow::pricemenu[16], MainWindow::tasete_balancemenu[16], "no","no");
    std::string answer = "yes";
    if (carbonationReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+0.5);
        drinkObj.ask_carbonated(answer);
    }

    if (alcoholReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+2.5);
        drinkObj.ask_alcohol(answer);
    }

    MainWindow::menuPtr->addItems(drinkObj);
}


void drinks::on_checkBox_4_clicked()
{
    QMessageBox::StandardButton carbonationReply;
    carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated?", QMessageBox::Yes | QMessageBox::No);

    QMessageBox::StandardButton alcoholReply;
    alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink?", QMessageBox::Yes | QMessageBox::No);

    Drink drinkObj(MainWindow::namemenu[17], MainWindow::pricemenu[17], MainWindow::tasete_balancemenu[17], "no","no");
    std::string answer = "yes";
    if (carbonationReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+0.5);
        drinkObj.ask_carbonated(answer);
    }

    if (alcoholReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+2.5);
        drinkObj.ask_alcohol(answer);
    }

    MainWindow::menuPtr->addItems(drinkObj);
}


void drinks::on_checkBox_3_clicked()
{
    QMessageBox::StandardButton carbonationReply;
    carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated?", QMessageBox::Yes | QMessageBox::No);

    QMessageBox::StandardButton alcoholReply;
    alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink?", QMessageBox::Yes | QMessageBox::No);

    Drink drinkObj(MainWindow::namemenu[18], MainWindow::pricemenu[18], MainWindow::tasete_balancemenu[18], "no","no");
    std::string answer = "yes";
    if (carbonationReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+0.5);
        drinkObj.ask_carbonated(answer);
    }

    if (alcoholReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+2.5);
        drinkObj.ask_alcohol(answer);
    }

    MainWindow::menuPtr->addItems(drinkObj);
}


void drinks::on_checkBox_5_clicked()
{
    QMessageBox::StandardButton carbonationReply;
    carbonationReply = QMessageBox::question(this, "Question", "Do you want your drink carbonated?", QMessageBox::Yes | QMessageBox::No);

    QMessageBox::StandardButton alcoholReply;
    alcoholReply = QMessageBox::question(this, "Question", "Do you want an additional alcohol shot in your drink?", QMessageBox::Yes | QMessageBox::No);

    Drink drinkObj(MainWindow::namemenu[19], MainWindow::pricemenu[19], MainWindow::tasete_balancemenu[19], "no","no");
    std::string answer = "yes";
    if (carbonationReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+0.5);
        drinkObj.ask_carbonated(answer);
    }

    if (alcoholReply == QMessageBox::Yes) {
        drinkObj.set_Foodprice(drinkObj.get_Foodprice()+2.5);
        drinkObj.ask_alcohol(answer);
    }

    MainWindow::menuPtr->addItems(drinkObj);
}

