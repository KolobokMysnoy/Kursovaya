#ifndef BUILDING_H
#define BUILDING_H

#include <QString>
#include <vector>
#include "interfaces.h"

class Building : public IBuilding
{
public:
    // get info about places
    QString get_all_toilets() override;
    QString get_all_canteens() override;
    QString get_all_relax() override;

    // get ways
    QString get_cab_way(size_t cab1, size_t cab2) override;
    QString get_loc_way(QString place) override;

    // set and get graph
    void set_graph(QString graph) override;
    QString get_graph() override;

    virtual ~Building();
private:
    ILocation * get_loc(size_t numb_of_loc);
    // search graph
    QString graph_search(size_t cab1, size_t cab2);
    std::vector <IFloor *> floors;

    short ** graph;
    size_t numbers;
};

//cabinets
class Room: public IRoom
{
public:
    bool init(QString str) override;

    QString get_info() override;
    QString get_type() override;
    size_t get_numb() override;

    virtual Room & operator =(const Room& other);

    QString get_save_info() override;

    virtual ~Room(){};
private:
    size_t numb;
    QString type;
    QString info;
};

//locs 
//TODO virtual constructor and operator =

class Loc: public ILocation
{
public:
    bool init(QString str) override;
    bool init_neighboors(way_loc &loc) override;

    QString search_way(ILocation * from_loc) override;
    IRoom * search_for_room(size_t cab) override;

    QString get_info() override;
    size_t get_numb() override;
    // info for save
    QString get_save_info() override;

    virtual Loc & operator =(const Loc & other);
    virtual ~Loc();
protected:
    QString info;
    size_t numb;

    std::vector <IRoom *> rooms;
    std::vector <way_loc> locs_with_ways;
};


//floors
class Floor: public IFloor
{
public:
    bool init(QString str) override;

    QString get_info_places() override;
    ILocation search_for_way(size_t cab1, size_t cab2) override;
    size_t get_numb() override;
    ILocation * search_for_loc(size_t loc_numb) override;

    QString get_save_info() override;

    virtual Floor & operator =(const Floor& other);
    virtual ~Floor();
private:
    std::vector <ILocation *> locs;
    QString info;
    size_t numb;
};

#endif // BUILDING_H
