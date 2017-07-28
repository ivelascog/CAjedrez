#include "UIBoard.h"


UIButtonLogic *UIBoard::getUIMap(int x, int y)
{
    if (x < width && y < height) {
        return uiMap[x][y];
    } else {
        throw runtime_error ("Error: out of bounds UI selection");
    }
}

void UIBoard::updateButtonLogic()
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (getTerrain()->getTMap(j,i)->isObstacle()) {
                getUIMap(j, i)->setBg(obstacle);
            } else {
                getUIMap(j,i)->setBg(def);
            }
            if (getUnits()->getUMap(j, i) != nullptr) {
                if (getUnits()->isHostile(getUnits()->getUMap(j, i)->getTeam(), myTeam)) {
                    getUIMap(j,i)->setFg(enemy);
                } else if (getUnits()->isFriendly(getUnits()->getUMap(j, i)->getTeam(), myTeam)) {
                    getUIMap(j,i)->setFg(me);
                } else if (getUnits()->isAlly(getUnits()->getUMap(j, i)->getTeam(), myTeam)) {
                    getUIMap(j,i)->setFg(ally);
                }
            }
            switch (units->isPosToDefend(j, i, myTeam)) {
                    case 1:
                        getUIMap(j, i)->setBorder(posToDefendMe);
                        break;
                    case 2:
                        getUIMap(j, i)->setBorder(posToDefendEnemy);
                        break;
                    case 3:
                        getUIMap(j, i)->setBorder(posToDefendAlly);
                        break;
                    default:
                        getUIMap(j, i)->setBorder(noBorder);
                        break;
            }
        }
    }
}

void UIBoard::updateButtonLogic(int x, int y)
{
    return updateButtonLogic(x, y, 0);
}

void UIBoard::updateButtonLogic(int x, int y, int moveExhaust)
{
    updateButtonLogic();
    if (units->getUMap(x, y) == nullptr) {
        return;
    }
    if (units->isHostile(units->getUMap(x, y)->getTeam(), myTeam)) {
        updateEnemy(x, y, moveExhaust);
    } else {
        updateAlly(x, y, moveExhaust);
    }
}

void UIBoard::updateAlly(int x, int y, int moveExhaust) {
    Unit *u = units->getUMap(x, y);
    vector<vector<int>> acc = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    if (u->getMoveP() > 0 && u->getAttP() > 0) {
        acc = accessibleAttacks(u, moveExhaust);
    } else if (u->getMoveP() > 0) {
        acc = accessible(u, moveExhaust);
    } else if (u->getAttP() > 0) {
        acc = inRange(u);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (acc[j][i] > 0) {
                    acc[j][i] = -3;
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (acc[j][i] == -3 && units->getUMap(j, i) == nullptr) {
                getUIMap(j, i)->setBg(inAttackRange);
            } else if (acc[j][i] == -3 && units->isHostile(myTeam, units->getUMap(j,i)->getTeam())) {
                getUIMap(j, i)->setBg(inAttackRangeandHostile);
                getUIMap(j, i)->setFg(white);
            } else if (acc[j][i] > 0) {
                getUIMap(j, i)->setBg(inMoveRange);
            }
            switch (units->isPosToDefend(j, i, myTeam)) {
                    case 1:
                        getUIMap(j, i)->setBorder(posToDefendMe);
                        break;
                    case 2:
                        getUIMap(j, i)->setBorder(posToDefendEnemy);
                        break;
                    case 3:
                        getUIMap(j, i)->setBorder(posToDefendAlly);
                        break;
                    default:
                        getUIMap(j, i)->setBorder(noBorder);
                        break;
            }
        }
    }
    getUIMap(x, y)->setBg(selected);
}

void UIBoard::updateEnemy(int x, int y, int moveExhaust) {
    Unit *u = units->getUMap(x, y);
    vector<vector<int>> acc = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    if (u->getMoveP() > 0 && u->getAttP() > 0) {
        acc = accessibleAttacks(u, moveExhaust);
    } else if (u->getMoveP() > 0) {
        acc = accessible(u, moveExhaust);
    } else if (u->getAttP() > 0) {
        acc = inRange(u);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (acc[j][i] > 0) {
                    acc[j][i] = -3;
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (acc[j][i] == -3 && units->getUMap(j, i) == nullptr) {
                getUIMap(j, i)->setBg(inAttackRange);
            } else if (acc[j][i] == -3 &&
                       (units->isFriendly(myTeam, units->getUMap(j,i)->getTeam()) || units->isAlly(myTeam, units->getUMap(j,i)->getTeam()))) {
                getUIMap(j, i)->setBg(inAttackRangeandHostile);
                getUIMap(j, i)->setFg(white);
            } else if (acc[j][i] > 0) {
                getUIMap(j, i)->setBg(inMoveRange);
            }
            switch (units->isPosToDefend(j, i, myTeam)) {
                    case 1:
                        getUIMap(j, i)->setBorder(posToDefendMe);
                        break;
                    case 2:
                        getUIMap(j, i)->setBorder(posToDefendEnemy);
                        break;
                    case 3:
                        getUIMap(j, i)->setBorder(posToDefendAlly);
                        break;
                    default:
                        getUIMap(j, i)->setBorder(noBorder);
                        break;
            }
        }
    }
    getUIMap(x, y)->setBg(selected);
}

void UIBoard::initUI(int team)
{
    uiMap = vector<vector<UIButtonLogic *>> ((unsigned long) width,
            std::vector<UIButtonLogic *>((unsigned long) height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uiMap[j][i] = new UIButtonLogic();
        }
    }
    myTeam = team;
}

UIBoard::~UIBoard()
{
    for (vector<UIButtonLogic*> v : uiMap) {
        for (UIButtonLogic *ub : v) {
            delete ub;
        }
        v.clear();
    }
    uiMap.clear();
}
