#include "floors.h"


bool Floor::init(QString str) {
    QList <QString> str_list = str.split('\n');
    QList <QString> information = str_list[0].split(':');

    if (information.length() != 4) return 0;
    if (information[0] != "floor") return 0;

    this->numb = information[1].toInt();
    this->locs.reserve(information[2].toInt());
    this->info = information[3];

    uint16_t i = 1;
    while(i < str_list.size() - 2) {
        locs[i] = new Loc;
        locs[i]->init(str_list[i-1]);
        ++i;
    }

    if (str_list[str_list.size()-1] != "end_floor\n") return 0;

    return 1;
}

QString Floor::get_info_places() {
    return this->info;
}

ILocation * Floor::search_for_loc(size_t loc_numb) {
    for(ILocation * i : locs) {
        if(i->get_numb() == loc_numb ) return i;
    }

    return nullptr;
}

QString Floor::get_save_info() {
    QString string_return;
    string_return = "floor:" + QString::number(this->numb) + ':' +
             QString::number(this->locs.size()) + ':' + this->info + '\n';

    for (size_t i = 0; i < this->locs.size()-1; ++i) {
        string_return.push_back(this->locs[i]->get_info());
    }

    string_return.push_back("end_floor\n");

    return string_return;
}

size_t Floor::get_numb() {
    return this->numb;
}

Floor::~Floor() {
    for(size_t i = 0; i < locs.size() - 1; ++i) {
        delete locs[i];
    }
}

ILocation * Floor::search_for_loc_by_room(size_t room) {
    for(ILocation * i : locs) {
        if (i->search_for_room(room) != nullptr) return i;
    }

    return nullptr;
}

