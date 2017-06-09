//
// Created by fer on 8/06/17.
//

#ifndef PROYECTO_GENERICUNIT_H
#define PROYECTO_GENERICUNIT_H

#include <stdlib.h>
#include <string>

using namespace std;

virtual class Unit {
protected:
    const int movm, health, damage, range;
    int posX, posY, cHealth, id, team;
    string name;
public:
    virtual bool isDead();

    virtual int dealDamage(int d);

    virtual string report();

    virtual void setTeam(int team);

    virtual void setID(int id);

    virtual void setPos(int x, int y);

    virtual void setName(string n);

    virtual string typeStats()= 0;

    const int getMovm() const;

    const int getHealth() const;

    const int getDamage() const;

    const int getRange() const;

    const int getId() const;

    const int getTeam() const;

    int getPosX() const;

    int getPosY() const;

    int getCHealth() const;

    const string &getName() const;
};


#endif //PROYECTO_GENERICUNIT_H
