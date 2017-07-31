#ifndef UIGAME_H
#define UIGAME_H

#include "Multiplayer/MultiplayerGame.h"
#include "UIBoard.h"
#include <QInputDialog>
#include <QMessageBox>

class UIGame : public MultiplayerGame
{
    bool okFlag;
    UIBoard *board;
public:
    void clientInit();

    void promptMessage(string s);

    void hostInit();

    UIBoard *getBoard();

    virtual void joinGame1();

    virtual void hostGame1();

    virtual void hostGameCastleAssault();

    virtual void joinGameCastleAssault();

    //TODO
    BGColor getBG(int x, int y);

    FGColor getFG(int x, int y);

    BorderColor getBorder(int x, int y);

    char getIcon(int x, int y);

    float getHealth(int x, int y);

    void advanceTurn();
};

#endif // UIGAME_H
