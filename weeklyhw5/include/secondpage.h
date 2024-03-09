#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QDialog>

namespace Ui {
class secondpage;
}

class secondpage : public QDialog
{
    Q_OBJECT

public:
    explicit secondpage(QWidget *parent = nullptr);
    ~secondpage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();


private:
    Ui::secondpage *ui;
};

#endif // SECONDPAGE_H
