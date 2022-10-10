#include "building.h"

bool Building::init(QString init_str) {
    QList <QString> floor = init_str.split("floor");

    QList <QString> build_params = floor[0].split(':');
    if (build_params[0] != "building") return 0;

    floors.reserve(build_params[1].toUInt());
    this->numbers = build_params[2].split('\n')[0].toUInt();

    for(size_t i = 1; i < floor.size() - 1; ++i) {
        // TODO
        //        floors[i-1] = new Floor;
        Floor * fl = new Floor;
        fl->init("floor" + floor[i]);
        floors.push_back(fl);
    }

    set_graph(floor[floor.size()-1]);

    return 1;
}

QString Building::save() {
    QString result;
    result = "building:" + QString::number(floors.size()) + ":" +
            QString::number(this->numbers) + '\n';

    for( IFloor * i: floors) {
        result += i->get_save_info();
    }
    result += "floor\n";
    result += get_graph();

    return result;
}

// All locations to our interests
// TODO
// Dummy functions
QString Building::get_all_canteens() {
    return "";
}

QString Building::get_all_relax() {
    return "";
}

QString Building::get_all_toilets() {
    return "";
}


// Ways beetween two
QString Building::get_way_between_locs(std::vector <ILocation *> locs) {
    QString result;

    size_t i = 0;
    while (i < locs.size()-2) {
        result += "," + locs[i+2]->search_way(locs[i]);
        ++i;
    }
    result += ',' + locs[locs.size() - 1]->search_way(locs[locs.size() - 2]);
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
            QString result = where_search[0]->search_way_to_room(info1[1].toUInt(),where_search[1],1);
            // get from loc to loc
            result += ',' + get_way_between_locs(where_search);
            // get from loc to room
            result += ',' + where_search[where_search.size()-1]->search_way_to_room(info2[1].toUInt(),where_search[where_search.size()-2]);

            return result;

        }
    }
    return "";
}


// Get location
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


// get way like array of loc 1->2->3
std::vector <ILocation *> Building::way_from_loc(size_t loc1, size_t loc2) {
    // TODO
    // DUMMY to search in graph
    std::vector <ILocation *> vec;
    vec.push_back(floors[0]->search_for_loc(1));
    vec.push_back(floors[0]->search_for_loc(2));
    vec.push_back(floors[0]->search_for_loc(3));
    vec.push_back(floors[0]->search_for_loc(5));
    vec.push_back(floors[0]->search_for_loc(6));
    return vec;
}


// set and get graph to save
void Building::set_graph(QString graph) {
    // TODO
    // Get warning

    if (graph.split(':')[0] != "\ngraph") return ;

    size_t column = 0;
    size_t str = 0;

    this->graph = new short [numbers * numbers];

    // graph:0.1.2.3 where 0.1.2.3 is our weight of edge
    QList <QString> ls = graph.split(':')[1].split('.');
    for(QString i: graph.split(':')[1].split('.')) {
        this->graph[column+numbers*str] = i.toUInt();

        ++column;
        if (column == numbers) {
            column=0;
            str+=1;
        }
    }

}

QString Building::get_graph() {
    QString result = "graph:";
    size_t column = 1;
    size_t str = 0;

    result += QString::number(this->graph[0]);

    while (str < numbers) {
        result += '.' + QString::number(this->graph[ str * numbers + column]);


        ++column;
        if (column == numbers) {
            column = 0;
            ++str;
        }
    }

    result += '\n';

    return result;
}


// virutals
Building & Building::operator=(const Building &other) {
    // TODO
    // Need = to graph transportation
    this->graph = other.graph;
    this->numbers = other.numbers;

    for(size_t i = 0; i < other.floors.size()-1; ++i) {
        // TODO
        // can broke because contains \n
        this->floors[i] = new Floor;
        this->floors[i]->init(other.floors[i]->get_save_info());
    }

    return *this;
}

Building::~Building() {
    for (IFloor * i: floors) {
        delete i;
    }
}
