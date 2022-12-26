#include "allinformationwid.h"

allInformationWid::allInformationWid()
{
    // buttons

    exitButton.setText(("Exit"));
//        exitButton.setText(("Exit"));
    outInformationButton.setText("Information output");

    // textOut
    outTextEdit.setReadOnly(true);

    // layouts
    mainVerticalLay.addWidget(&outTextEdit);
    mainVerticalLay.addWidget(&outInformationButton);
    mainVerticalLay.addWidget(&exitButton);

    this->setLayout(&mainVerticalLay);

    // connections
    QObject::connect(&exitButton,&QPushButton::clicked,[this]{this->close();});
    QObject::connect(&outInformationButton,&QPushButton::clicked,[this]{outTextEdit.setText(outInformation());});
}

QString allInformationWid::outInformation() {
    QString res;
    QString tempForSplit;

    // toilets
    tempForSplit = _bui->get_all_toilets();
    for (auto informationAboutToilet : tempForSplit.split('\n')){
        if (informationAboutToilet == "") continue;
        res += "Òףאכועû :" + informationAboutToilet + '\n';
    }

    // relax
    tempForSplit = _bui->get_all_relax();
    for (auto informationAboutRelax : tempForSplit.split('\n')){
        if (informationAboutRelax == "") continue;
        res += "Îעהûץ :" + informationAboutRelax + '\n';
    }

    // food
    tempForSplit = _bui->get_all_canteens();
    for (auto informationAboutFood : tempForSplit.split('\n')){
        if (informationAboutFood == "") continue;
        res += "Åהא :" + informationAboutFood + '\n';
    }

    return res;
};
