#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "building.h"
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void set();
    Building * bui;
    QVBoxLayout *vbox;
    QPushButton *but;
    QTextEdit *ed1;
    QTextEdit *ed2;
    QTextEdit *ed3;

};

#endif // MAINWINDOW_H
