#include "mainwindow.h"
#include <QFile>
#include <QString>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    bui = new Building;

    QFile file("in.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QString result;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        result += line;
    }

    bui->set_graph(result);

    vbox = new QVBoxLayout(this);
    but = new QPushButton;
    ed1 = new QTextEdit;
    ed2 = new QTextEdit;
    ed3 = new QTextEdit;

    vbox->addWidget(ed1);
    vbox->addWidget(ed2);
    vbox->addWidget(ed3);
    vbox->addWidget(but);

    QObject::connect(but,&QPushButton::clicked,[this]{this->set();});

    // TOOD
    // MEMORY LOSS
    QWidget *wid;
    wid->setLayout(vbox);
    this->setCentralWidget(wid);
}

void MainWindow::set(){
    ed3->setText(bui->get_way(ed1->toPlainText(),ed2->toPlainText()));
}

MainWindow::~MainWindow()
{
    delete bui;

    delete vbox;
    delete but;
    delete ed1;
    delete ed2;
    delete ed3;
}

