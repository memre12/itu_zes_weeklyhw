#ifndef STARTER_H
#define STARTER_H

#include <QDialog>

namespace Ui {
class starter;
}

class starter : public QDialog
{
    Q_OBJECT

public:
    explicit starter(QWidget *parent = nullptr);
    ~starter();

private slots:


    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::starter *ui;
};

#endif // STARTER_H
