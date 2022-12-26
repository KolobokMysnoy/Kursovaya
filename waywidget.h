#ifndef WAYWIDGET_H
#define WAYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "building.h"

class WayWidget: public QWidget
{
public:
    WayWidget();
    void getBui(IBuilding* bui);
    QVBoxLayout vbox;
    QLineEdit lineFrom;
    QHBoxLayout hbox;

    QPushButton buttonForSearchPath;
    QPushButton buttonToExit;

    // text editor
    QLineEdit lineTo;
    QTextEdit result;
private:
    IBuilding * _bui;
};

#endif // WAYWIDGET_H
