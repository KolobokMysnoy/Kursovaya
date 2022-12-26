#ifndef GETWAYTOLOCS_H
#define GETWAYTOLOCS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QComboBox>

#include "building.h"

class GetWayToLocs : public QWidget
{
    Q_OBJECT
public:
    GetWayToLocs();
    void getBui(IBuilding * bui);
    QLineEdit lineFromCab;
    QTextEdit results;

    QPushButton ButtonExit;
    QPushButton ButtonSearch;

    QVBoxLayout mainLay;
    QHBoxLayout buttonLay;
    QVBoxLayout radioLay;

    QRadioButton FoodBut;
    QRadioButton ToiletBut;
    QRadioButton RestBut;

    QComboBox comboToCheck;
private:
    IBuilding * _bui;
    QString getWay();
    size_t choosen();
    void insertElementsInCombo(const QString str, QComboBox & box);
    void insertion(size_t ind);
};

#endif // GETWAYTOLOCS_H
