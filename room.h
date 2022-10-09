#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <vector>
#include "interfaces.h"
#include <QList>

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

#endif // ROOM_H
