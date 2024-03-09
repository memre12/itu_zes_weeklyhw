#ifndef DRINKS_H
#define DRINKS_H

#include <QDialog>

namespace Ui {
class drinks;
}

class drinks : public QDialog
{
    Q_OBJECT

public:
    explicit drinks(QWidget *parent = nullptr);
    ~drinks();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::drinks *ui;
};

#endif // DRINKS_H
