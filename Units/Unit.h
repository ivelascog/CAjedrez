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
    int maxMoveP = 1;
    int maxAttP = 1;
    string name;
    Types type;
    char icon = '?';
    string iconName;
public:
    void setCHealth(int cHealth);

    Types getType() const;

    int getMoveP() const;

    void setMoveP(int moveP);

    int getAttP() const;

    void setAttP(int attP);

    //Devuelve true si la ud esta muerta (cHealth == 0);
    virtual bool isDead();

    //string con info ud
    virtual string report();

    virtual void setTeam(int team);

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

    //Reduce el cHealth de la unidad
    void takeDamage(int damageTaken);

    //devuelve puntos de atq y mov a 1
    void resetAP();

    //reduce puntos de atq
    void reduceAttP();

    //reduce puntos de mov
    void reduceMovP();

    char getIcon();

    //Report del ID y la pos de la ud.
    string miniReport();
    string getIconName() const;
};


#endif //PROYECTO_GENERICUNIT_H
