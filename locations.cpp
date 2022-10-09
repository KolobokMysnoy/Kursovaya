#include "locations.h"

bool Loc::init(QString str) {
    QList <QString> str_list = str.split('\n');
    QList <QString> information = str_list[0].split(':');

    if (information.length() != 4) return 0;
    if (information[0] != "location") return 0;

    this->rooms.reserve(information[1].toInt());
    this->numb = information[2].toInt();
    this->info = information[3];

    uint16_t i = 1;
    while(i < str_list.size() - 2) {
        rooms[i-1] = new Room;
        rooms[i-1]->init(str_list[i]);
        ++i;
    }

    if (str_list[str_list.size()-1] != "end_location\n") return 0;

    return 1;
}

bool Loc::init_neighboors(way_loc &loc) {
    this->locs_with_ways.push_back(loc);
    return 1;
}

QString Loc::search_way_to_room(size_t cab, ILocation * loc, bool from_to) {
    for(way_room i: rooms_with_ways) {
        if (i.room == cab && i.loc == loc->get_numb()) {
            if (from_to) {
                return i.from;
            } else {
                return i.to;
            }
        }
    }
}

QString Loc::search_way(ILocation *from_loc) {
    size_t numb_of_loc = from_loc->get_numb();
    for(way_loc i: locs_with_ways) {
        if (i.numb == numb_of_loc) return i.way;
    }
    return "";
}

IRoom * Loc::search_for_room(size_t cab){
    for(size_t i = 0; i < this->rooms.size(); ++i) {
        if (this->rooms[i]->get_numb() == cab) return this->rooms[i];
    }
    return nullptr;
}

QString Loc::get_info(){
    return this->info;
}

size_t Loc::get_numb(){
    return this->numb;
}

QString Loc::get_save_info(){
    QString string_return;
    string_return = "location:" + QString::number(this->rooms.size()) + ':' +
            QString::number(this->numb) + ':' + this->info + '\n';

    for (size_t i = 0; i < rooms.size()-1; ++i) {
        string_return.push_back(rooms[i]->get_info());
    }

    string_return.push_back("end_location\n");

    return string_return;
}

Loc & Loc::operator=(const Loc &other) {
    this->info = other.info;
    this->numb = other.numb;

    for(size_t i = 0; i < other.rooms.size()-1; ++i) {
        // TODO
        // can broke because contains \n
        this->rooms[i] = new Room;
        this->rooms[i]->init(other.rooms[i]->get_save_info());
    }

    this->locs_with_ways = other.locs_with_ways;

    return *this;
}

Loc::~Loc() {
    for(size_t i = 0; i<rooms.size() - 1; ++i) {
        delete rooms[i];
    }
}
