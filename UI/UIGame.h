#ifndef UIGAME_H
#define UIGAME_H

#include "Multiplayer/MultiplayerGame.h"
#include <QInputDialog>
#include <QMessageBox>

class UIGame : public MultiplayerGame
{
    bool okFlag;
public:
    void clientInit();

    void promptMessage(string s);

    void hostInit();
};

#endif // UIGAME_H
