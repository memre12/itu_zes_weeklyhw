#ifndef SALADS_H
#define SALADS_H

#include <QDialog>

namespace Ui {
class Salads;
}

class Salads : public QDialog
{
    Q_OBJECT

public:
    explicit Salads(QWidget *parent = nullptr);
    ~Salads();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::Salads *ui;
};

#endif // SALADS_H
