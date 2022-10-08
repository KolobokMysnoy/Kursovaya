#include "building.h"
#include <QList>



//---------------ROOMS---------------------------

bool Room::init(QString str) {
    QList <QString>str_list = str.split(':');

    if (str_list.length() != 4) return 0;
    if (str_list[0] != "room") return 0;

    this->numb = str_list[1].toInt();
    this->type = str_list[2];
    this->info = str_list[3];

    return 1;
}

QString Room::get_info() {
    return this->info;
}

QString Room::get_type() {
    return this->type;
}

size_t Room::get_numb() {
    return this->numb;
}

QString Room::get_save_info(){
    return "room:" + QString::number(this->numb) + ':' +
            type + ':' + info + '\n';
}

Room & Room::operator=(const Room& other){
    this->numb = other.numb;
    this->type = other.type;;
    this->info = other.info;

    return *this;
}
//---------------ROOMS---------------------------

//---------------Loc---------------------------

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

QString Loc::search_way(ILocation *from_loc) {

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

//---------------Loc---------------------------

//---------------FLOOR-------------------------
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

ILocation Floor::search_for_way(size_t cab1, size_t cab2) {

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
//---------------FLOOR-------------------------

//---------------FLOOR-------------------------

//---------------Building----------------------
QString Building::get_all_canteens() {

}

QString Building::get_all_relax() {

}

QString Building::get_all_toilets() {

}

QString Building::get_cab_way(size_t cab1, size_t cab2) {
    // WARNING !!!!!
    // this method is dummy !!!
    // results = 1:2:3:4:5:6 ...
    QList <QString> results = algorithm_search(graph, numbers, cab1,
                                       cab2).split(':');

    std::vector <ILocation *> loc_where_search;
    loc_where_search.reserve(results.size());

    // array of location to search
    // 1->2->3->4->5
    for(size_t i = 0; i< results.size() - 1; ++i ) {
        loc_where_search[i] = get_loc(results[i].toUInt());
    }

    QString result;
    if(loc_where_search.size() < 3) {
        result.push_back(loc_where_search[1]->search_way(loc_where_search[0]));
    } else {
    //  from 0 to 2, from 2 to 4
        for(size_t i = 2; i < loc_where_search.size() - 1; ++i) {
            result.push_back(loc_where_search[1]->search_way(loc_where_search[i-2])+',');
        }
    }

    return result;
}

QString Building::get_loc_way(QString place) {

}

void Building::set_graph(QString graph) {

}

QString Building::get_graph() {

}

Building::~Building() {

}

QString Building::graph_search(size_t cab1, size_t cab2) {



}

ILocation * Building::get_loc(size_t numb_of_loc) {
    for(IFloor * i : floors) {
        ILocation * tmp = i->search_for_loc(numb_of_loc);
        if (tmp != nullptr) return tmp;
    }

    return nullptr;
}
//---------------Building----------------------
