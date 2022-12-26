#include "locations.h"

// init our location
bool Loc::init(QString str) {
    // split string to our params
    QList <QString> params = str.split("room:");

    // get info about
    QList <QString> str_list = params[0].split('\n');
    QList <QString> information = str_list[0].split(':');

    if (information.length() != 4) return 0;
    if (information[0] != "location") return 0;

    this->rooms.reserve(information[1].toInt());
    this->numb = information[2].toInt();
    this->info = information[3];

    // get ways to locations
    information = str_list[1].split('{');
    if(information[0] != "way_loc") return 0;

    // ways reserve
    QList <QString> params_of_ways = information[1].split(':');
    locs_with_ways.reserve(params_of_ways[0].toUInt());

    for (size_t i = 1; i < params_of_ways.size(); ++i) {
        QList <QString> param_to_way = params_of_ways[i].split(',');

        // TODO
        way_loc lc;
        lc.way = param_to_way[1];
        lc.numb = param_to_way[0].toUInt();
        locs_with_ways.push_back(lc);
//        locs_with_ways[i-1].numb = param_to_way[0].toUInt();
//        locs_with_ways[i-1].way = param_to_way[1];
    }

    // rooms
    uint16_t i = 1;
    while(i < params.size()) {
//        rooms[i-1] = new Room;
//        rooms[i-1]->init("room:" + params[i]);
        // TODO
        Room * rm = new Room;
        rm->init("room:" + params[i]);
        rooms.push_back(rm);
        ++i;
    }

    return 1;
}


// search for wayå
QString Loc::search_way_to_room(size_t cab, ILocation * loc, bool from_to) {
    for(IRoom * i: rooms) {
        if (i->get_numb() == cab) {
            return i->get_way_from_loc(loc, from_to);
        }
    }

    return "";
}

QString Loc::search_way(ILocation *from_loc) {
    size_t numb_of_loc = from_loc->get_numb();
    for(way_loc i: locs_with_ways) {
        if (i.numb == numb_of_loc) return i.way;
    }
    return "";
}

// search for room in location
IRoom * Loc::search_for_room(size_t cab){
    for(size_t i = 0; i < this->rooms.size(); ++i) {
        if (this->rooms[i]->get_numb() == cab) return this->rooms[i];
    }
    return nullptr;
}


// get info
QString Loc::get_info(){
    return this->info;
}

size_t Loc::get_numb(){
    return this->numb;
}

QString Loc::get_save_info(){
    QString string_return;
    // general info
    string_return = "location:" + QString::number(this->rooms.size()) + ':' +
            QString::number(this->numb) + ':' + this->info + '\n';

    // ways info
    string_return += "way_loc{" + QString::number(locs_with_ways.size());
    for (way_loc i: locs_with_ways){
        string_return += ':' + QString::number(i.numb) +',' + i.way;
    }

    string_return +="{\n";

    // rooms info
    for (size_t i = 0; i < rooms.size(); ++i) {
        string_return += rooms[i]->get_save_info();
    }


    return string_return;
}


// virtual
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
    if (rooms.size() != 0 ) {
        for(size_t i = 0; i<rooms.size() - 1; ++i) {
            delete rooms[i];
        }
    }
}
