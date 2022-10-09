#ifndef FLOORS_H
#define FLOORS_H

#include <QString>
#include <vector>
#include "interfaces.h"
#include <QList>

#include "locations.h"


class Floor: public IFloor
{
public:
    bool init(QString str) override;

    QString get_info_places() override;
//    ILocation search_for_way(size_t cab1, size_t cab2) override;
    size_t get_numb() override;
    ILocation * search_for_loc(size_t loc_numb) override;
    ILocation * search_for_loc_by_room(size_t room) override;

    QString get_save_info() override;

    virtual Floor & operator =(const Floor& other);
    virtual ~Floor();
private:
    std::vector <ILocation *> locs;
    QString info;
    size_t numb;
};

#endif // FLOORS_H
