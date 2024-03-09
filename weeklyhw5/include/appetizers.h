#ifndef APPETIZERS_H
#define APPETIZERS_H

#include <QDialog>

namespace Ui {
class appetizers;
}

class appetizers : public QDialog
{
    Q_OBJECT

public:
    explicit appetizers(QWidget *parent = nullptr);
    ~appetizers();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::appetizers *ui;
};

#endif // APPETIZERS_H
