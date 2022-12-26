#include "waywidget.h"


WayWidget::WayWidget(): QWidget()
{
//    setlocale(LC_ALL,"Russian");

    // create all buttons
    buttonForSearchPath.setText(("Search"));
    buttonToExit.setText(("Exit"));

    // text editor
    lineFrom.setText(("From"));
    lineTo.setText("To");
    result.setText("");
    result.setReadOnly(true);

    // containers to store buttons etc
    hbox.addWidget(&buttonForSearchPath);
    hbox.addWidget(&buttonToExit);

    vbox.addWidget(&lineFrom);
    vbox.addWidget(&lineTo);
    vbox.addWidget(&result);

    vbox.addLayout(&hbox);

//     connects
    QObject::connect(&buttonForSearchPath,&QPushButton::clicked, [this]{result.setText(this->_bui->get_way("room:" + lineFrom.text(), "room:" + lineTo.text()));});
    QObject::connect(&buttonToExit,&QPushButton::clicked, [this] { this->close();});
    this->setLayout(&vbox);
}

void WayWidget::getBui(IBuilding *bui) {
    _bui = bui;
}


