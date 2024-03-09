#include "salads.h"
#include "ui_salads.h"
#include "mainwindow.h"
#include "QListWidgetItem"
#include "menu_titles.h"
#include "QWidgetItem"
#include "QMessageBox"

Salads::Salads(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Salads)
{
    ui->setupUi(this);
    for (int var = 5; var < 10; ++var) {
        QString saladInfo = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
        ui->salad_list->addItem(new QListWidgetItem(saladInfo));
        if(var<9){
            ui->salad_list->addItem(new QListWidgetItem("\n"));
        }
    }
}

Salads::~Salads()
{
    delete ui;
}

void Salads::on_pushButton_clicked() {
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}

void Salads::on_pushButton_2_clicked()
{

}


void Salads::on_checkBox_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want to add topic", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // User clicked Yes, proceed with adding the salad
        Salad salads(MainWindow::namemenu[5], MainWindow::pricemenu[5], MainWindow::tasete_balancemenu[5],1);

        salads.set_Foodprice(salads.get_Foodprice()+2.25);
        MainWindow::menuPtr->addItems(salads);
    } else {
        // User clicked No, do nothing or handle as required
        Salad salads(MainWindow::namemenu[5], MainWindow::pricemenu[5], MainWindow::tasete_balancemenu[5],0);
        MainWindow::menuPtr->addItems(salads);
    }
}


void Salads::on_checkBox_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want to add topic", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // User clicked Yes, proceed with adding the salad
        Salad salads(MainWindow::namemenu[6], MainWindow::pricemenu[6], MainWindow::tasete_balancemenu[6],1);

        salads.set_Foodprice(salads.get_Foodprice()+2.25);
        MainWindow::menuPtr->addItems(salads);
    } else {
        // User clicked No, do nothing or handle as required
        Salad salads(MainWindow::namemenu[6], MainWindow::pricemenu[6], MainWindow::tasete_balancemenu[6],0);
        MainWindow::menuPtr->addItems(salads);
    }
}


void Salads::on_checkBox_4_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want to add topic", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // User clicked Yes, proceed with adding the salad
        Salad salads(MainWindow::namemenu[7], MainWindow::pricemenu[7], MainWindow::tasete_balancemenu[7],1);

        salads.set_Foodprice(salads.get_Foodprice()+2.25);
        MainWindow::menuPtr->addItems(salads);
    } else {
        // User clicked No, do nothing or handle as required
        Salad salads(MainWindow::namemenu[7], MainWindow::pricemenu[7], MainWindow::tasete_balancemenu[7],0);
        MainWindow::menuPtr->addItems(salads);
    }
}


void Salads::on_checkBox_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want to add topic", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // User clicked Yes, proceed with adding the salad
        Salad salads(MainWindow::namemenu[8], MainWindow::pricemenu[8], MainWindow::tasete_balancemenu[8],1);
        salads.set_Foodprice(salads.get_Foodprice()+2.25);
        MainWindow::menuPtr->addItems(salads);
    } else {
        // User clicked No, do nothing or handle as required
        Salad salads(MainWindow::namemenu[8], MainWindow::pricemenu[8], MainWindow::tasete_balancemenu[8],0);
        MainWindow::menuPtr->addItems(salads);
    }
}


void Salads::on_checkBox_5_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want to add topic", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // User clicked Yes, proceed with adding the salad
        Salad salads(MainWindow::namemenu[9], MainWindow::pricemenu[9], MainWindow::tasete_balancemenu[9],1);
        salads.set_Foodprice(salads.get_Foodprice()+2.25);
        MainWindow::menuPtr->addItems(salads);

    } else {
        // User clicked No, do nothing or handle as required
        Salad salads(MainWindow::namemenu[9], MainWindow::pricemenu[9], MainWindow::tasete_balancemenu[9],0);
        MainWindow::menuPtr->addItems(salads);
    }
}
