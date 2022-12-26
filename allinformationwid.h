#ifndef ALLINFORMATIONWID_H
#define ALLINFORMATIONWID_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QComboBox>

#include "building.h"

class allInformationWid : public QWidget
{
public:
    allInformationWid();

    QVBoxLayout mainVerticalLay;

    QPushButton exitButton;
    QPushButton outInformationButton;

    QTextEdit outTextEdit;

    void setBuilding(IBuilding * bui) {_bui = bui;};
private:
    QString outInformation();

    IBuilding * _bui;
};

#endif // ALLINFORMATIONWID_H
