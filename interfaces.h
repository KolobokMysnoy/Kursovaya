#ifndef INTERFACES_H
#define INTERFACES_H

#include <QString>
#include <vector>
//#include "search_graph.cpp"

/*
    FIle
    It will contain first string which will help us with identification

    Build::floors{}
        floor::numb::


*/


// loc file
// name_loc:strl:strr:strs:locl:loc1:loc2:locr:loc2:loc3:locs
// location:numb_of_rooms:numb:info\n
// rooms...
// end_location

// room file
// room:number:type:info

// floor file
// floor:numb:numb_of_locs:info\n

// locs with way

//struct to way from location
class ILocation;

typedef struct {
    size_t numb;
    QString way;
} way_loc;

// struct for rooms

typedef struct {
    size_t room;
    size_t loc;
    QString from;
    QString to;
} way_room;

//interfaces

class IRoom
{
public:
    // initialize room
    virtual bool init(QString str) = 0;

    // info about room for expand
    virtual QString get_info() = 0;
    // info about type of cabinet for expand
    virtual QString get_type() = 0;
    // info about number for search
    virtual size_t get_numb() = 0;
    // info for save
    virtual QString get_save_info() = 0;

    IRoom & operator = (const IRoom& other);
    virtual ~IRoom() = 0;
};

class ILocation
{
public:
    // initialize location
    virtual bool init(QString str) = 0;

    // initialize left locations
    virtual bool init_neighboors(way_loc &loc) = 0;

    // search way between locs
    virtual QString search_way(ILocation * from_loc) = 0;
    // search way to room
    virtual QString search_way_to_room(size_t cab, ILocation * loc, bool from_to = 0) = 0;
    // search for room. if doesn't have then nullptr
    virtual IRoom * search_for_room(size_t cab) = 0;

    // get additional info
    virtual QString get_info() = 0;
    // get info about number in graph search
    virtual size_t get_numb() = 0;
    // info for save
    virtual QString get_save_info() = 0;

    ILocation & operator = (const ILocation& other);
    virtual ~ILocation() = 0;
};

class IFloor
{
public:
    // initialize floor
    virtual bool init(QString str) = 0;

    // get info about places
    virtual QString get_info_places() = 0;
    virtual size_t get_numb() = 0;
    // search betwe en locations in floor
//    virtual ILocation search_for_way(size_t cab1, size_t cab2) = 0;
    // info for save
    virtual QString get_save_info() = 0;

    virtual ILocation * search_for_loc(size_t loc_numb) = 0;
    virtual ILocation * search_for_loc_by_room(size_t room) = 0;

    IFloor & operator=(const IFloor& other);
    virtual ~IFloor() = 0;
};

class IBuilding
{
public:
    virtual bool init(QString init_str) = 0;

    // get info about places
    virtual QString get_all_toilets() = 0;
    virtual QString get_all_canteens() = 0;
    virtual QString get_all_relax() = 0;

    // get ways
    virtual QString get_way(QString from, QString to) = 0;
//    virtual QString get_loc_way(QString place) = 0;

    // set and get graph
    virtual void set_graph(QString graph) = 0;
    virtual QString get_graph() = 0;

    IBuilding & operator=(const IBuilding& other);
    virtual ~IBuilding() = 0;
};



#endif // INTERFACES_H
