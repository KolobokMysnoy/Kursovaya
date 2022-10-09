#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QString>
#include <vector>
#include "interfaces.h"
#include <QList>
#include "room.h"

class Loc: public ILocation
{
public:
    bool init(QString str) override;

    QString search_way(ILocation * from_loc) override;
    IRoom * search_for_room(size_t cab) override;
    QString search_way_to_room(size_t cab, ILocation * loc, bool from_to = 0) override;

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

#endif // LOCATIONS_H
