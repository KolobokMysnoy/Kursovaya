#include "room.h"

// init room
bool Room::init(QString str, QString ways) {
    // Was Changed
    // TODO
    QList <QString> param = str.split('\n');
    QList <QString >str_list = param[0].split(':');

    // init room informations
    if (str_list.length() < 4) return 0;
    if (str_list[0] != "room") return 0;

    this->numb = str_list[1].toInt();
    this->type = str_list[2];
    this->info = str_list[3];

    // init ways
    ways = param[1];
    if(ways == "") return 0;

    str_list = param[1].split('{');
    if(str_list[0] != "way_room") return 0;

    QList <QString> way_list = str_list[1].split(':');
    ways_from_to_room.reserve(way_list[0].toUInt());

    for (size_t i = 1; i < way_list.size(); ++i) {
        QList <QString> params = way_list[i].split(',');
        // TODO
        way_room wr;
        wr.from = params[1];
        wr.to = params[2];
        wr.loc = params[0].toUInt();
        ways_from_to_room.push_back(wr);
//        ways_from_to_room[i-1].loc = params[0].toUInt();
//        ways_from_to_room[i-1].from = params[1];
//        ways_from_to_room[i-1].to = params[2];
    }

    return 1;
}


// info about room
QString Room::get_info() {
    return this->info;
}

QString Room::get_type() {
    return this->type;
}

size_t Room::get_numb() {
    return this->numb;
}


// info to save room
QString Room::get_save_info(){
    QString result = "room:" + QString::number(this->numb) + ':' +
            type + ':' + info + '\n' + "way_room{" +
            QString::number(ways_from_to_room.size());

    for(way_room i: ways_from_to_room) {
        result += ':' + QString::number(i.loc) + ',' +
                i.from + ',' + i.to;
    }

    result  += "{\n";

    return result;
}

// get way to near locations
QString Room::get_way_from_loc(ILocation *loc, bool from) {
    for (way_room i: ways_from_to_room) {
        if (i.loc == loc->get_numb()){
            if (from){
                return i.from;
            } else {
                return i.to;
            }
        }
    }
    return "";
}

// virtual
Room & Room::operator=(const Room& other){
    this->numb = other.numb;
    this->type = other.type;;
    this->info = other.info;

    return *this;
}

Room::~Room() {

}
