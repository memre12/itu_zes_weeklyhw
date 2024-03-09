#ifndef MENU_REC_H
#define MENU_REC_H

#include <QDialog>

namespace Ui {
class menu_rec;
}

class menu_rec : public QDialog
{
    Q_OBJECT

public:
    explicit menu_rec(QWidget *parent = nullptr);
    ~menu_rec();
    int sweet;
    int sour;
    int bitter;
    int savory;
    int salty;

private slots:
    void on_sweet_valueChanged(int value);

    void on_pushButton_clicked();

    void on_sour_valueChanged(int value);

    void on_bitter_valueChanged(int value);

    void on_salty_valueChanged(int value);

    void on_savory_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::menu_rec *ui;
};

#endif // MENU_REC_H
