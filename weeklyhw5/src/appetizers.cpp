#include "appetizers.h"
#include "ui_appetizers.h"
#include "mainwindow.h"
#include "menu_titles.h"
#include "QMessageBox"

appetizers::appetizers(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::appetizers)
{
    ui->setupUi(this);
    for (int var = 20; var < 25; ++var) {
        QString saladInfo = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
        ui->appetizer_list->addItem(new QListWidgetItem(saladInfo));
        if(var<24){
            ui->appetizer_list->addItem(new QListWidgetItem("\n"));
        }
    }
}

appetizers::~appetizers()
{
    delete ui;
}

void appetizers::on_pushButton_clicked()
{
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}


void appetizers::on_checkBox_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "When do you want the appetizer to be served?", QMessageBox::Yes | QMessageBox::No);

    QString servingTime = (reply == QMessageBox::Yes) ? "before" : "after";

    if(servingTime == "before"){
        Appetizer appetizer(MainWindow::namemenu[20], MainWindow::pricemenu[20], MainWindow::tasete_balancemenu[20], "before");
        MainWindow::menuPtr->addItems(appetizer);
    }else{
        Appetizer appetizer(MainWindow::namemenu[20], MainWindow::pricemenu[20], MainWindow::tasete_balancemenu[20], "after");
        MainWindow::menuPtr->addItems(appetizer);
    }
}


void appetizers::on_checkBox_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "When do you want the appetizer to be served?", QMessageBox::Yes | QMessageBox::No);

    QString servingTime = (reply == QMessageBox::Yes) ? "before" : "after";

    if(servingTime == "before"){
        Appetizer appetizer(MainWindow::namemenu[21], MainWindow::pricemenu[21], MainWindow::tasete_balancemenu[21], "before");
        MainWindow::menuPtr->addItems(appetizer);
    }else{
        Appetizer appetizer(MainWindow::namemenu[21], MainWindow::pricemenu[21], MainWindow::tasete_balancemenu[21], "after");
        MainWindow::menuPtr->addItems(appetizer);
    }
}


void appetizers::on_checkBox_4_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "When do you want the appetizer to be served?", QMessageBox::Yes | QMessageBox::No);

    QString servingTime = (reply == QMessageBox::Yes) ? "before" : "after";

    if(servingTime == "before"){
        Appetizer appetizer(MainWindow::namemenu[22], MainWindow::pricemenu[22], MainWindow::tasete_balancemenu[22], "before");
        MainWindow::menuPtr->addItems(appetizer);
    }else{
        Appetizer appetizer(MainWindow::namemenu[22], MainWindow::pricemenu[22], MainWindow::tasete_balancemenu[22], "after");
        MainWindow::menuPtr->addItems(appetizer);
    }
}


void appetizers::on_checkBox_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "When do you want the appetizer to be served?", QMessageBox::Yes | QMessageBox::No);

    QString servingTime = (reply == QMessageBox::Yes) ? "before" : "after";

    if(servingTime == "before"){
        Appetizer appetizer(MainWindow::namemenu[23], MainWindow::pricemenu[23], MainWindow::tasete_balancemenu[23], "before");
        MainWindow::menuPtr->addItems(appetizer);
    }else{
        Appetizer appetizer(MainWindow::namemenu[23], MainWindow::pricemenu[23], MainWindow::tasete_balancemenu[23], "after");
        MainWindow::menuPtr->addItems(appetizer);
    }
}


void appetizers::on_checkBox_5_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "When do you want the appetizer to be served?", QMessageBox::Yes | QMessageBox::No);

    QString servingTime = (reply == QMessageBox::Yes) ? "before" : "after";

    if(servingTime == "before"){
        Appetizer appetizer(MainWindow::namemenu[24], MainWindow::pricemenu[24], MainWindow::tasete_balancemenu[24], "before");
        MainWindow::menuPtr->addItems(appetizer);
    }else{
        Appetizer appetizer(MainWindow::namemenu[24], MainWindow::pricemenu[24], MainWindow::tasete_balancemenu[24], "after");
        MainWindow::menuPtr->addItems(appetizer);
    }
}

