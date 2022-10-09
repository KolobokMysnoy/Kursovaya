#include "building.h"

QString Building::get_all_canteens() {
    return "";
}

QString Building::get_all_relax() {
    return "";
}

QString Building::get_all_toilets() {
    return "";
}


QString Building::get_way_between_locs(std::vector <ILocation *> locs) {
    QString result;

    size_t i = 0;
    while (i < locs.size()-2) {
        result += "," + locs[i+2]->search_way(locs[i]);
        ++i;
    }
    result += ',' + locs[locs.size()-2]->search_way(locs[locs.size()-1]);
    return result;
}

QString Building::get_way(QString from, QString to) {
    // from location:numb|room:numb
    // to location:numb|room:numb

    std::vector <ILocation *> where_to_search;

    QList <QString> info1 = from.split(':');
    QList <QString> info2 = to.split(':');

    if (info1[0] == "location") {
        if (info2[0] == "location") {
            // from loc to loc
            return get_way_between_locs(way_from_loc(info1[1].toUInt(),info2[1].toUInt()));
        } else {
            // from loc to room

            // where to search
            std::vector <ILocation *> where_search = way_from_loc(info1[1].toUInt(), get_loc_by_room(info2[1].toUInt())->get_numb());

            // get from loc to loc
            QString result = get_way_between_locs(where_search);

            // get from loc to room
            result += ',' + where_search[where_search.size()-1]->search_way_to_room(info2[1].toUInt(),where_search[where_search.size()-2]);

            return result;

        }
    } else {
        if (info2[0] == "location") {
            // from room to location

            // where to search
            std::vector <ILocation *> where_search = way_from_loc(get_loc_by_room(info1[1].toUInt())->get_numb(),info2[1].toUInt());

            // get from room to loc
            QString result = where_search[0]->search_way_to_room(info2[1].toUInt(),where_search[1],1);
            // get from loc to loc
            result += ',' + get_way_between_locs(where_search);

            return result;
        } else {
            // from room to room

            // locs from to
            ILocation * loc1 = get_loc_by_room(info1[1].toUInt());
            ILocation * loc2 = get_loc_by_room(info2[1].toUInt());

            // where to search
            std::vector <ILocation *> where_search = way_from_loc(loc1->get_numb(),loc2->get_numb());

            // get from room to loc
            QString result = where_search[0]->search_way_to_room(info2[1].toUInt(),where_search[1],1);
            // get from loc to loc
            result += ',' + get_way_between_locs(where_search);
            // get from loc to room
            result += ',' + where_search[where_search.size()-1]->search_way_to_room(info2[1].toUInt(),where_search[where_search.size()-2]);

            return result;

        }
    }
    return "";
}

ILocation * Building::get_loc_by_room(size_t room) {
    for(IFloor * i : floors) {
        ILocation * loc = i->search_for_loc_by_room(room);
        if (loc != nullptr)
            return loc;
    }

    return nullptr;
}

ILocation * Building::get_loc(size_t numb_of_loc) {
    for(IFloor * i : floors) {
        ILocation * tmp = i->search_for_loc(numb_of_loc);
        if (tmp != nullptr) return tmp;
    }

    return nullptr;
}

std::vector <ILocation *> Building::way_from_loc(size_t loc1, size_t loc2) {
    // TODO
    // DUMMY to search in graph
}

Building::~Building() {
    for (IFloor * i: floors) {
        delete i;
    }
}

void Building::set_graph(QString graph) {
    // TODO
}

QString Building::get_graph() {
    // TODO
    return "";
}
