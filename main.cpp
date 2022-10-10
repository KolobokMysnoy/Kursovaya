#include "mainwindow.h"

#include <QApplication>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QFile>



void set(QTextEdit *ed1,QTextEdit *ed2,QTextEdit *ed3, Building *bui){
    ed3->setText(bui->get_way(ed1->toPlainText(),ed2->toPlainText()));
}

QString res(QTextEdit *ed4,Building *bui){
    bui->init(ed4->toPlainText());
    return bui->save();
}
int main(int argc, char *argv[])
{
    Building * bui;
    QVBoxLayout *vbox;
    QPushButton *but;
    QTextEdit *ed1;
    QTextEdit *ed2;
    QTextEdit *ed3;
    QTextEdit *ed4;

    QApplication a(argc, argv);
    bui = new Building;
    QPushButton *but1 = new QPushButton;
    but1->setText("But1");

//    QString result;


    vbox = new QVBoxLayout;
    but = new QPushButton;
    ed1 = new QTextEdit;
    ed2 = new QTextEdit;
    ed3 = new QTextEdit;
    ed4 = new QTextEdit;

    vbox->addWidget(ed1);
    vbox->addWidget(ed2);
    vbox->addWidget(ed3);
    vbox->addWidget(but);
    vbox->addWidget(ed4);
    vbox->addWidget(but1);

    QObject::connect(but,&QPushButton::clicked,[ed1,ed2,ed3,bui]{set(ed1,ed2,ed3,bui);});
    QObject::connect(but1,&QPushButton::clicked,[ed4,bui,ed3]{ed3->setText(res(ed4,bui));});

    ed1->setText("1:1");
    ed2->setText("2:2");
//    bui->init("QString()")

    // TOOD
    // MEMORY LOSS
    QWidget wid;
    wid.setLayout(vbox);
    wid.show();
//    w.show();
    return a.exec();
}
