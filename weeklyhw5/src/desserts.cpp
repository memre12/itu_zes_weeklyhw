#include "desserts.h"
#include "ui_desserts.h"
#include "menu_titles.h"
#include "mainwindow.h"
#include "Menu.h"
#include "QMessageBox"

desserts::desserts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::desserts)
{
    ui->setupUi(this);
    for (int var = 25; var < 30; ++var) {
        QString saladInfo = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
        ui->dessert_list->addItem(new QListWidgetItem(saladInfo));
        if(var<29){
            ui->dessert_list->addItem(new QListWidgetItem("\n"));
        }
    }

}

desserts::~desserts()
{
    delete ui;
}

void desserts::on_pushButton_clicked()
{
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}

void desserts::on_checkBox_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want extra chocolate?", QMessageBox::Yes | QMessageBox::No);

    double extraCost = (reply == QMessageBox::Yes) ? 1.5 : 0.0;
    Dessert dessert(MainWindow::namemenu[25], MainWindow::pricemenu[25], MainWindow::tasete_balancemenu[25], (reply == QMessageBox::Yes) ? "yes" : "no");
    dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);
    MainWindow::menuPtr->addItems(dessert);
}


void desserts::on_checkBox_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want extra chocolate?", QMessageBox::Yes | QMessageBox::No);

    double extraCost = (reply == QMessageBox::Yes) ? 1.5 : 0.0;
    Dessert dessert(MainWindow::namemenu[26], MainWindow::pricemenu[26], MainWindow::tasete_balancemenu[26], (reply == QMessageBox::Yes) ? "yes" : "no");
    dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);
    MainWindow::menuPtr->addItems(dessert);
}


void desserts::on_checkBox_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want extra chocolate?", QMessageBox::Yes | QMessageBox::No);

    double extraCost = (reply == QMessageBox::Yes) ? 1.5 : 0.0;
    Dessert dessert(MainWindow::namemenu[28], MainWindow::pricemenu[28], MainWindow::tasete_balancemenu[28], (reply == QMessageBox::Yes) ? "yes" : "no");
    dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);
    MainWindow::menuPtr->addItems(dessert);
}


void desserts::on_checkBox_4_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want extra chocolate?", QMessageBox::Yes | QMessageBox::No);

    double extraCost = (reply == QMessageBox::Yes) ? 1.5 : 0.0;
    Dessert dessert(MainWindow::namemenu[27], MainWindow::pricemenu[27], MainWindow::tasete_balancemenu[27], (reply == QMessageBox::Yes) ? "yes" : "no");
    dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);
    MainWindow::menuPtr->addItems(dessert);
}


void desserts::on_checkBox_5_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want extra chocolate?", QMessageBox::Yes | QMessageBox::No);

    double extraCost = (reply == QMessageBox::Yes) ? 1.5 : 0.0;
    Dessert dessert(MainWindow::namemenu[29], MainWindow::pricemenu[29], MainWindow::tasete_balancemenu[29], (reply == QMessageBox::Yes) ? "yes" : "no");
    dessert.set_Foodprice(dessert.get_Foodprice()+extraCost);
    MainWindow::menuPtr->addItems(dessert);
}

