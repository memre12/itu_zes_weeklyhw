#include "secondpage.h"
#include "ui_secondpage.h"
#include "menu_titles.h"
#include "show_chosen_menu.h"
#include "menu_rec.h"
secondpage::secondpage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondpage)
{
    ui->setupUi(this);
}

secondpage::~secondpage()
{
    delete ui;
}

void secondpage::on_pushButton_clicked() {
    this->hide();
    menu_titles *titles = new menu_titles(this);
    titles->setModal(true);
    titles->exec();
}


void secondpage::on_pushButton_3_clicked()
{
    QApplication::exit(true);
}


void secondpage::on_pushButton_2_clicked()
{
    this->hide();
    show_chosen_menu *chosenmenu = new show_chosen_menu(this);
    chosenmenu->setModal(true);
    chosenmenu->exec();
}


void secondpage::on_pushButton_4_clicked()
{
    this->hide();
    menu_rec *rec = new menu_rec(this);
    rec->setModal(true);
    rec->exec();
}




