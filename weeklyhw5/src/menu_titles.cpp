#include "menu_titles.h"
#include "ui_menu_titles.h"
#include "salads.h"
#include "starter.h"
#include "appetizers.h"
#include "main_courses.h"
#include "drinks.h"
#include "desserts.h"
#include "secondpage.h"

menu_titles::menu_titles(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu_titles)
{
    ui->setupUi(this);
}

menu_titles::~menu_titles()
{
    delete ui;
}

void menu_titles::on_pushButton_3_clicked()
{
    this->hide();

    Salads* saladsWidget = new Salads(this);
    saladsWidget->setModal(true);
    saladsWidget->exec();
}


void menu_titles::on_pushButton_clicked()
{
    this->hide();

    starter *asda = new starter(this);
    asda->setModal(true);
    asda->exec();
}


void menu_titles::on_pushButton_4_clicked()
{
    this->hide();

    appetizers *app = new appetizers(this);
    app->setModal(true);
    app->exec();
}


void menu_titles::on_pushButton_2_clicked()
{
    this->hide();

    main_courses *app = new main_courses(this);
    app->setModal(true);
    app->exec();
}


void menu_titles::on_pushButton_5_clicked()
{
    this->hide();

    drinks *app = new drinks(this);
    app->setModal(true);
    app->exec();
}


void menu_titles::on_pushButton_6_clicked()
{
    this->hide();

    desserts *app = new desserts(this);
    app->setModal(true);
    app->exec();
}


void menu_titles::on_pushButton_7_clicked()
{
    this->hide();
    secondpage *secpag = qobject_cast<secondpage*>(parentWidget());
    if (secpag) {
        secpag->show();
    } else {
        qDebug() << "Parent widget is null or not of type secondpage.";
    }
}

