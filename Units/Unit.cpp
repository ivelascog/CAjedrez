//
// Created by fer on 8/06/17.
//

#include "Unit.h"

using namespace std;

int Unit::uId = 0;

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

void Unit::setTeam(int team) {
    this->team = team;
}

string Unit::report() {
    return name + " (ID " + to_string(id) + "):\tHealth: " + to_string(cHealth) + "/" + to_string(health) +
           "\tPos: (" +
           to_string(posX) +
           ", " + to_string(posY) + ")  /\tAP: Mov = " + to_string(moveP) + " Att = " + to_string(attP);
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

int Unit::getAttP() const {
    return attP;
}

void Unit::setAttP(int attP) {
    Unit::attP = attP;
}

int Unit::getMoveP() const {
    return moveP;
}

void Unit::setMoveP(int moveP) {
    Unit::moveP = moveP;
}

void Unit::resetAP() {
    moveP = maxMoveP;
    attP = maxAttP;
}

void Unit::reduceAttP() {
    attP -= 1;
}

void Unit::reduceMovP() {
    moveP -= 1;
}

string Unit::typeStats() {
    return "\t\t\t\tMov: " + to_string(movm) + "\tHealth: " + to_string(health) + "\tDamage: " +
           to_string(damage) +
           "\tRange: " + to_string(range);
}

Types Unit::getType() const {
    return type;
}

void Unit::setCHealth(int cHealth) {
    Unit::cHealth = cHealth;
}

char Unit::getIcon() {
    return icon;
}

string Unit::miniReport() {
    return name + " (ID " + to_string(id) + ")\tPos: (" + to_string(getPosX()) + ", " + to_string(getPosY()) + ")\n";
}

