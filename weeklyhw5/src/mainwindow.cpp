#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include <iostream>
#include "secondpage.h"
#include "QMessageBox"

std::shared_ptr<Menu> MainWindow::menuPtr = std::make_shared<Menu>();
std::vector<std::string> MainWindow::namemenu;
std::vector<double> MainWindow::pricemenu;
std::vector<std::vector<int>> MainWindow::tasete_balancemenu;
std::vector<int> MainWindow::balanceforcalc;
Menu MainWindow::men;
std::shared_ptr<User> MainWindow::user = std::make_shared<User>("", "");


static readjson x;


MainWindow::MainWindow(QWidget *parent1)
    : QMainWindow(parent1)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x.fill_items();
    for (const auto& element : x.willaddname) {
        namemenu.push_back(element);
    }
    for (const auto& element : x.willaddprice) {
        pricemenu.push_back(element);
    }
    for (const auto& element : x.willaddtaste_balance_total) {
        tasete_balancemenu.push_back(element);
    }
    User user("","");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()) {
        ui->checkBox_2->setChecked(false); // Uncheck the other checkbox
    }
}

void MainWindow::on_checkBox_2_clicked()
{
    if (ui->checkBox_2->isChecked()) {
        ui->checkBox->setChecked(false); // Uncheck the other checkbox
    }
}

void MainWindow::on_pushButton_clicked()
{

    // Assign name and surname from line edits
    QString surnamea = ui->lineEdit->text();
    QString namea = ui->lineEdit_2->text();

    // Reset title
    QString title = "";

    // Determine title based on checkbox selection
    if (ui->checkBox->isChecked()) {
        title = "Mr.";
        ui->checkBox_2->setChecked(false); // Uncheck the other checkbox
    } else if (ui->checkBox_2->isChecked()) {
        title = "Mrs.";
        ui->checkBox->setChecked(false); // Uncheck the other checkbox
    }
    std::string namea_std = namea.toStdString();
    std::string surnamea_std = surnamea.toStdString();
    std::string title_std = title.toStdString();

    if((ui->checkBox->isChecked() || ui->checkBox_2->isChecked()) && !namea_std.empty() && !surnamea_std.empty()){
        this->hide();
        s.setModal(true);
        s.exec();
    }else{
        QString errorMessage = "You must fill checkbox, name and surname.";

        // Show the error message in a QMessageBox
        QMessageBox::critical(this, "Critical Error", errorMessage);
    }
    MainWindow::user->set_gender(title_std);
    MainWindow::user->set_name(namea_std);
    MainWindow::user->set_surname(surnamea_std);
    std::cout << title_std << " " << namea_std << " " << surnamea_std << std::endl;
}
