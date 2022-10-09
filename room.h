#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <vector>
#include "interfaces.h"
#include <QList>

class Room: public IRoom
{
public:
    bool init(QString str, QString ways = "") override;

    QString get_info() override;
    QString get_type() override;
    size_t get_numb() override;

    virtual Room & operator =(const Room& other);

    virtual QString get_way_from_loc(ILocation *loc, bool from = 0) override;

    QString get_save_info() override;

    virtual ~Room();
private:
    size_t numb;
    QString type;
    QString info;
    std::vector <way_room> ways_from_to_room;
};

#endif // ROOM_H
