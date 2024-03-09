#include "starter.h"
#include "ui_starter.h"
#include "mainwindow.h"
#include "menu_titles.h"
#include "QMessageBox"


starter::starter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::starter)
{
    ui->setupUi(this);
    for (int var = 0; var < 5; ++var) {
        QString saladInfo = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
        ui->starter_list->addItem(new QListWidgetItem(saladInfo));
        if(var<4){
            ui->starter_list->addItem(new QListWidgetItem("\n"));
        }
    }
}

starter::~starter()
{
    delete ui;
}


void starter::on_pushButton_2_clicked()
{
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}


void starter::on_checkBox_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no", QMessageBox::Yes | QMessageBox::No);
    QString servingTemperature = (reply == QMessageBox::Yes) ? "hot" : "cold";

    if(servingTemperature == "hot"){
        Starter start(MainWindow::namemenu[0], MainWindow::pricemenu[0], MainWindow::tasete_balancemenu[0],"hot");
        MainWindow::menuPtr->addItems(start);

    }else{
        Starter start(MainWindow::namemenu[0], MainWindow::pricemenu[0], MainWindow::tasete_balancemenu[0],"cold");
        MainWindow::menuPtr->addItems(start);
    }
}


void starter::on_checkBox_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no", QMessageBox::Yes | QMessageBox::No);
    QString servingTemperature = (reply == QMessageBox::Yes) ? "hot" : "cold";

    if(servingTemperature == "hot"){
        Starter start(MainWindow::namemenu[1], MainWindow::pricemenu[1], MainWindow::tasete_balancemenu[1],"hot");
        MainWindow::menuPtr->addItems(start);

    }else{
        Starter start(MainWindow::namemenu[1], MainWindow::pricemenu[1], MainWindow::tasete_balancemenu[1],"cold");
        MainWindow::menuPtr->addItems(start);
    }
}


void starter::on_checkBox_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no", QMessageBox::Yes | QMessageBox::No);
    QString servingTemperature = (reply == QMessageBox::Yes) ? "hot" : "cold";

    if(servingTemperature == "hot"){
        Starter start(MainWindow::namemenu[2], MainWindow::pricemenu[2], MainWindow::tasete_balancemenu[2],"hot");
        MainWindow::menuPtr->addItems(start);

    }else{
        Starter start(MainWindow::namemenu[2], MainWindow::pricemenu[2], MainWindow::tasete_balancemenu[2],"cold");
        MainWindow::menuPtr->addItems(start);
    }
}


void starter::on_checkBox_4_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no", QMessageBox::Yes | QMessageBox::No);
    QString servingTemperature = (reply == QMessageBox::Yes) ? "hot" : "cold";

    if(servingTemperature == "hot"){
        Starter start(MainWindow::namemenu[3], MainWindow::pricemenu[3], MainWindow::tasete_balancemenu[3],"hot");
        MainWindow::menuPtr->addItems(start);

    }else{
        Starter start(MainWindow::namemenu[3], MainWindow::pricemenu[3], MainWindow::tasete_balancemenu[3],"cold");
        MainWindow::menuPtr->addItems(start);
    }
}


void starter::on_checkBox_5_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Question", "Do you want the starter to be served hot or cold?(if hot, click yes/ if cold, click no", QMessageBox::Yes | QMessageBox::No);
    QString servingTemperature = (reply == QMessageBox::Yes) ? "hot" : "cold";

    if(servingTemperature == "hot"){
        Starter start(MainWindow::namemenu[4], MainWindow::pricemenu[4], MainWindow::tasete_balancemenu[4],"hot");
        MainWindow::menuPtr->addItems(start);

    }else{
        Starter start(MainWindow::namemenu[4], MainWindow::pricemenu[4], MainWindow::tasete_balancemenu[4],"cold");
        MainWindow::menuPtr->addItems(start);
    }
}

