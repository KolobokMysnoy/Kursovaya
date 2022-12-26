#include "floors.h"

// init floor
bool Floor::init(QString str) {
    // TODO
    // Warnings from below
    QList <QString> loc_list = str.split("location");

    // floor info
    QList <QString> str_list = loc_list[0].split('\n');
    QList <QString> information = str_list[0].split(':');

    if (information.length() < 4) return 0;
    if (information[0] != "floor") return 0;

    this->numb = information[1].toInt();
    this->locs.reserve(information[2].toInt());
    this->info = information[3];

    // locations
    uint16_t i = 1;
    while(i < loc_list.size()) {
        Loc *lc = new Loc;
        lc->init("location" + loc_list[i]);
        locs.push_back(lc);
//        locs[i-1] = new Loc;
//        locs[i-1]->init("location" + loc_list[i]);
        ++i;
    }

    return 1;
}


// info about floor
QString Floor::get_save_info() {
    // general info
    QString string_return;
    string_return = "floor:" + QString::number(this->numb) + ':' +
            QString::number(this->locs.size()) + ':' + this->info + '\n';
    // CHANGES
    //    todo

    // locs info
    for (size_t i = 0; i < this->locs.size(); ++i) {
        string_return += this->locs[i]->get_save_info();
    }

    return string_return;
}

size_t Floor::get_numb() {
    return this->numb;
}

QString Floor::get_info_places() {
    return this->info;
}


// search for loc
ILocation * Floor::search_for_loc_by_room(size_t room) {
    for(ILocation * i : locs) {
        if (i->search_for_room(room) != nullptr) return i;
    }

    return nullptr;
}

ILocation * Floor::search_for_loc(size_t loc_numb) {
    for(ILocation * i : locs) {
        if(i->get_numb() == loc_numb ) return i;
    }

    return nullptr;
}


// virtual
Floor & Floor::operator =(const Floor& other) {
    this->info = other.info;
    this->numb = other.numb;

    for(size_t i = 0; i < other.locs.size()-1; ++i) {
        // TODO
        // can broke because contains \n
        this->locs[i] = new Loc;
        this->locs[i]->init(other.locs[i]->get_save_info());
    }

    return *this;
}

Floor::~Floor() {
    for(size_t i = 0; i < locs.size() - 1; ++i) {
        delete locs[i];
    }
}

std::vector<size_t> Floor::countLocs() {
    std::vector<size_t> res;
    for(size_t i = 0; i < locs.size(); ++i) {
        res.push_back(locs[i]->get_numb());
    }
    return res;
}
