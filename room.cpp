#include "room.h"


bool Room::init(QString str) {
    QList <QString >str_list = str.split(':');

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
