#include "getwaytolocs.h"

GetWayToLocs::GetWayToLocs(): QWidget()
{
    // text
    lineFromCab.setText("Room");
    results.setText("");
    results.setReadOnly(true);

    // buttons
    ButtonExit.setText("Exit");
    ButtonSearch.setText("Search");

    //radio
    FoodBut.setText("Food");
    ToiletBut.setText("WC");
    RestBut.setText("Relax");

    // layouts
    buttonLay.addWidget(&ButtonExit);
    buttonLay.addWidget(&ButtonSearch);

    mainLay.addWidget(&lineFromCab);

    mainLay.addWidget(&FoodBut);
    mainLay.addWidget(&ToiletBut);
    mainLay.addWidget(&RestBut);
    mainLay.addWidget(&comboToCheck);
    mainLay.addWidget(&results);

    mainLay.addLayout(&buttonLay);

    this->setLayout(&mainLay);

    // connections
    QObject::connect(&ButtonExit,&QPushButton::clicked, [this] { this->close();});
    QObject::connect(&ButtonSearch,&QPushButton::clicked, [this] {insertion(choosen());});

    QObject::connect(&FoodBut, &QRadioButton::clicked, [this] {insertElementsInCombo(_bui->get_all_canteens(),comboToCheck);});
    QObject::connect(&ToiletBut, &QRadioButton::clicked, [this] {insertElementsInCombo(_bui->get_all_toilets(),comboToCheck);});
    QObject::connect(&RestBut, &QRadioButton::clicked, [this] {insertElementsInCombo(_bui->get_all_relax(),comboToCheck);});

}

size_t GetWayToLocs::choosen() {
    return comboToCheck.currentIndex();
}

void GetWayToLocs::insertion(size_t ind) {
    QString locationId = comboToCheck.itemText(ind).split(':')[0].split(' ')[0];
    results.setText(_bui->get_way("room:" + lineFromCab.text(), "location:" + locationId));
}

void GetWayToLocs::insertElementsInCombo(const QString str, QComboBox & box) {
    QList<QString> allLocations = str.split('\n');
    box.clear();
    for(qsizetype i = 0; i < allLocations.size() - 1; ++i) {
        box.insertItem(i, allLocations[i]);
    }
}
QString GetWayToLocs::getWay() {
    //TODO delete
}

void GetWayToLocs::getBui(IBuilding * bui) {
    _bui = bui;
}
