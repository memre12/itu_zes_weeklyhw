#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <secondpage.h>
#include "Menu.h"
#include "readjson.h"

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static Menu men;
    static std::shared_ptr<Menu> menuPtr;
    static std::vector<std::string> namemenu;
    static std::vector<double> pricemenu;
    static std::vector<std::vector<int>> tasete_balancemenu;
    static std::vector<int> balanceforcalc;
    static std::shared_ptr<User> user;

    QString names;
    QString surnames;
    QString yxz;
    secondpage s;

    readjson x;

    ~MainWindow();

private slots:

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
