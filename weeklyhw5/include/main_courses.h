#ifndef MAIN_COURSES_H
#define MAIN_COURSES_H

#include <QDialog>

namespace Ui {
class main_courses;
}

class main_courses : public QDialog
{
    Q_OBJECT

public:
    explicit main_courses(QWidget *parent = nullptr);
    ~main_courses();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::main_courses *ui;
};

#endif // MAIN_COURSES_H
