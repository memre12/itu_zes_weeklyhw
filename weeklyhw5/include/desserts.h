#ifndef DESSERTS_H
#define DESSERTS_H

#include <QDialog>

namespace Ui {
class desserts;
}

class desserts : public QDialog
{
    Q_OBJECT

public:
    explicit desserts(QWidget *parent = nullptr);
    ~desserts();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::desserts *ui;
};

#endif // DESSERTS_H
