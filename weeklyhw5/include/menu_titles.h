#ifndef MENU_TITLES_H
#define MENU_TITLES_H
#include <QDialog>

namespace Ui {
class menu_titles;
}

class menu_titles : public QDialog
{
    Q_OBJECT

public:
    explicit menu_titles(QWidget *parent = nullptr);


    ~menu_titles();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::menu_titles *ui;
};

#endif // MENU_TITLES_H
