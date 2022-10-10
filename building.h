#ifndef BUILDING_H
#define BUILDING_H

#include <QString>
#include <vector>
#include "interfaces.h"
#include <QList>

#include "floors.h"
#include "locations.h"

class Building : public IBuilding
{
public:
    bool init(QString init_str) override;
    virtual QString save() override;

    // get info about places
    QString get_all_toilets() override;
    QString get_all_canteens() override;
    QString get_all_relax() override;

    // get ways
    QString get_way(QString from, QString to) override;

    // set and get graph
    void set_graph(QString graph) override;
    QString get_graph() override;


    virtual Building & operator=(const Building& other);
    virtual ~Building();
private:
    QString get_way_between_locs(std::vector <ILocation *> locs);

    // get vector like 1:2:3:4:5
    std::vector <ILocation *> way_from_loc(size_t loc1, size_t loc2);

    ILocation * get_loc(size_t numb_of_loc);
    ILocation * get_loc_by_room(size_t room);

    // search graph
    QString graph_search(size_t cab1, size_t cab2);
    std::vector <IFloor *> floors;

    short * graph;
    size_t numbers;
};


#endif // BUILDING_H
