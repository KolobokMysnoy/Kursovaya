//#include "mainwindow.h"

#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QFile>

#include "waywidget.h"
#include "getwaytolocs.h"
#include "allinformationwid.h"

#include <building.h>

const QString STANDART_FILE = "C:/Kursovaya/build-Kurs-Desktop_Qt_6_0_4_MinGW_64_bit-Debug/debug/doc.txt";

void set(QTextEdit *ed1,QTextEdit *ed2,QTextEdit *ed3, Building *bui){
    ed3->setText(bui->get_way(ed1->toPlainText(),ed2->toPlainText()));
}


Building * readFromFile(Building ** bui, const QString string) {
    QString str = string != "" ? string : STANDART_FILE;
    (*bui) = new Building;
    QFile file(str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return *bui;

    QString initAll;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        initAll += line;
    }
    (*bui)->init(initAll);
    return *bui;
}

QString res(QTextEdit *ed4,Building *bui){
    bui->init(ed4->toPlainText());
    return bui->save();
}
int main(int argc, char *argv[])
{
//    setlocale(LC_ALL,"Russian");
//    QLocale::setDefault(QLocale::Russian);

    Building * bui = nullptr;
    QVBoxLayout vbox;

    QApplication a(argc, argv);

    // create all buttons
    QPushButton buttonForEditText("Upload filename");

    QPushButton buttonToSearchOfPath("Search for path");
    QPushButton buttonToSearchToiletOrFood("Search for food or toilet");
    QPushButton buttonToSearchForInfo("Info");
    QPushButton buttonToExit("Exit");

    // text editor
    QTextEdit editForNameOfFile("");

    // containers to store buttons etc
//    vbox = new QVBoxLayout();
    vbox.addWidget(&editForNameOfFile);
    vbox.addWidget(&buttonForEditText);
    vbox.addWidget(&buttonToSearchOfPath);
    vbox.addWidget(&buttonToSearchToiletOrFood);
    vbox.addWidget(&buttonToSearchForInfo);
    vbox.addWidget(&buttonToExit);

    // windows
    WayWidget pathWid;
    GetWayToLocs locsPathWid;
    allInformationWid infoWid;

//     connects
    QWidget wid;
    QObject::connect(&buttonForEditText,&QPushButton::clicked, [&bui, &editForNameOfFile]{readFromFile(&bui, editForNameOfFile.toPlainText());});

    QObject::connect(&buttonToSearchOfPath,&QPushButton::clicked, [&bui,&pathWid]{pathWid.getBui(bui);pathWid.show();});
    QObject::connect(&buttonToSearchToiletOrFood,&QPushButton::clicked, [&bui,&locsPathWid]{locsPathWid.getBui(bui); locsPathWid.show();});
    QObject::connect(&buttonToSearchForInfo,&QPushButton::clicked, [&bui,&infoWid]{infoWid.setBuilding(bui); infoWid.show();});

    QObject::connect(&buttonToExit,&QPushButton::clicked, [&a, &bui, &wid] { if(bui != nullptr) {delete bui;}; wid.close(); ;a.quit();});
//    bui->init("QString()");

    // TOOD
    // MEMORY LOSS
//    QWidget wid;
    wid.setLayout(&vbox);
    wid.show();
//    w.show();
    return a.exec();
}

