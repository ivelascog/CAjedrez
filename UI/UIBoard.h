#ifndef UIBOARD_H
#define UIBOARD_H

#include "Multiplayer/MultiplayerBoard.h"
#include "UIButtonLogic.h"


class UIBoard : public MultiplayerBoard
{
    vector<vector<UIButtonLogic *>> uiMap;
    int myTeam;
public:
    UIButtonLogic * getUIMap(int x, int y);

    void updateButtonLogic ();

    void updateButtonLogic (int x, int y);

    void initUI(int team);

    ~UIBoard();

    void updateAlly(int x, int y, int moveExhaust);

    void updateEnemy(int x, int y, int moveExhaust);

    void updateButtonLogic(int x, int y, int moveExhaust);
};

#endif // UIBOARD_H
