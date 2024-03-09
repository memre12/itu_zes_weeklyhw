#ifndef SHOW_CHOSEN_MENU_H
#define SHOW_CHOSEN_MENU_H

#include <QDialog>

namespace Ui {
class show_chosen_menu;
}

class show_chosen_menu : public QDialog
{
    Q_OBJECT

public:
    explicit show_chosen_menu(QWidget *parent = nullptr);
    ~show_chosen_menu();
    int n;

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::show_chosen_menu *ui;
};

#endif // SHOW_CHOSEN_MENU_H
