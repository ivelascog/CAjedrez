//
// Created by fer on 8/06/17.
//

#include <bits/basic_string.h>
#include "Unit.h"

using namespace std;

bool Unit::isDead() {
    return (cHealth <= 0);
}

void Unit::takeDamage(int damageTaken) {
    cHealth -= damageTaken;
    if (cHealth < 0)
        cHealth = 0;
}

void Unit::setName(string n) {
    name = n;
}

void Unit::setPos(int x, int y) {
    posX = x;
    posY = y;
}

void Unit::setID(int id) {
    this->id = id;
}

void Unit::setTeam(int team) {
    this->team = team;
}

int Unit::dealDamage(int d) {
    return 0;
}

string Unit::report() {
    return "Unit: "name + "\tHealth: " + to_string(cHealth) + "/" + to_string(health) + "\tPos: (" + to_string(posX) +
           ", " + to_string(posY) + ")";
}

const int Unit::getMovm() const {
    return movm;
}

const int Unit::getHealth() const {
    return health;
}

const int Unit::getDamage() const {
    return damage;
}

const int Unit::getRange() const {
    return range;
}

const int Unit::getId() const {
    return id;
}

const int Unit::getTeam() const {
    return team;
}

int Unit::getPosX() const {
    return posX;
}

int Unit::getPosY() const {
    return posY;
}

int Unit::getCHealth() const {
    return cHealth;
}

const string &Unit::getName() const {
    return name;
}
