#include "main_courses.h"
#include "ui_main_courses.h"
#include "mainwindow.h"
#include "menu_titles.h"
#include "QMessageBox"
#include "Menu.h"

main_courses::main_courses(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::main_courses)
{
    ui->setupUi(this);
    int vegetarianScore = QMessageBox::question(this, "Question", "Are you vegetarian?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes ? 13 : 10;

    if(vegetarianScore==13){
        ui->checkBox->hide();
        ui->checkBox_2->hide();
        ui->checkBox_4->hide();
    }
    for (int var = vegetarianScore; var < 15; ++var) {
        if(var == 13){
            QString maincourses = "\n\n\n" + QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
            ui->main_courses_list->addItem(new QListWidgetItem(maincourses));
            if(var<14){
                ui->main_courses_list->addItem(new QListWidgetItem("\n\n\n"));
            }
        }else{
            QString maincourses = QString::fromStdString(MainWindow::namemenu[var]) + " - " + QString::number(MainWindow::pricemenu[var]) + " $";
            ui->main_courses_list->addItem(new QListWidgetItem(maincourses));
            if(var<14){
                ui->main_courses_list->addItem(new QListWidgetItem("\n"));
            }
        }

    }
}

main_courses::~main_courses()
{
    delete ui;
}

void main_courses::on_pushButton_clicked()
{
    this->hide();
    menu_titles *titles = qobject_cast<menu_titles*>(parentWidget());
    if (titles) {
        titles->show();
    } else {
        qDebug() << "Parent widget is null or not of type menu_titles.";
    }
}


void main_courses::on_checkBox_clicked()
{
    MainCourse maincours(MainWindow::namemenu[10], MainWindow::pricemenu[10], MainWindow::tasete_balancemenu[10],"");
    MainWindow::menuPtr->addItems(maincours);
}


void main_courses::on_checkBox_2_clicked()
{
    MainCourse maincours1(MainWindow::namemenu[11], MainWindow::pricemenu[11], MainWindow::tasete_balancemenu[11],"");
    MainWindow::menuPtr->addItems(maincours1);
}


void main_courses::on_checkBox_4_clicked()
{
    MainCourse maincours1(MainWindow::namemenu[12], MainWindow::pricemenu[12], MainWindow::tasete_balancemenu[12],"");
    MainWindow::menuPtr->addItems(maincours1);
}


void main_courses::on_checkBox_3_clicked()
{
    MainCourse maincours1(MainWindow::namemenu[13], MainWindow::pricemenu[13], MainWindow::tasete_balancemenu[13],"");
    MainWindow::menuPtr->addItems(maincours1);
}


void main_courses::on_checkBox_5_clicked()
{
    MainCourse maincours1(MainWindow::namemenu[14], MainWindow::pricemenu[14], MainWindow::tasete_balancemenu[14],"");
    MainWindow::menuPtr->addItems(maincours1);
}

