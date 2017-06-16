//
// Created by fer on 8/06/17.
//

#ifndef PROYECTO_GENERICUNIT_H
#define PROYECTO_GENERICUNIT_H

#include <stdlib.h>
#include <string>
#include "UnitNames.h"

using namespace std;

enum Types {
    king = 0, soldier = 1, archer = 2, horse = 3
};

class Unit {
protected:
    static int uId;
    int movm, health, damage, range;
    int posX, posY, cHealth, id, team, moveP, attP;
    string name;
    Types type;
public:
    void setCHealth(int cHealth);

    Types getType() const;

    int getMoveP() const;

    void setMoveP(int moveP);

    int getAttP() const;

    void setAttP(int attP);

    virtual bool isDead();

    //string con info ud
    virtual string report();

    virtual void setTeam(int team);

    virtual void setID(int id);

    virtual void setPos(int x, int y);

    virtual void setName(string n);

    //string con info de clase
    string typeStats();

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

    void takeDamage(int damageTaken);

    //devuelve puntos de atq y mov a 1
    void resetAP();

    //reduce puntos de atq
    void reduceAttP();

    //reduce puntos de mov
    void reduceMovP();
};


#endif //PROYECTO_GENERICUNIT_H
