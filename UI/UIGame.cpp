#include "UIGame.h"

void UIGame::clientInit()
{
    okFlag = false;
    isHost = false;
    bool loop = true;
    string aux;

    while (loop) {
        aux = QInputDialog::getText(0, "Connecting to host", "Introduce Host IP:", QLineEdit::Normal, nullptr, &loop, Qt::Widget, Qt::ImhNone).toStdString();

        if (loop) {
            try {
                client = new Client(aux);
                loop = false;
            } catch (exception &e) {
                promptMessage("Error: couldn't connect to specified IP");
            }
        } else {
            return; //exit game
        }
    }

    client->write(board->getUnits()->getMapIdentifier());
    string aux2 = client->read();

    if (board->getUnits()->getMapIdentifier() != aux2) {
        promptMessage("Error: host game is '" + aux2 + "'");
        delete client;
        return;
    }

    vector<bool> avTeams = vector<bool> ((unsigned long) board->getUnits()->getTeams(), false);

    for (int i = 0; i < avTeams.size(); i++) {
        avTeams[i] = (client->read() == "1");
    }


    QStringList qsl;
    for (int i = 0; i < board->getUnits()->getTeamNames().size(); i++) {
        if (avTeams[i]) {
            aux2 = board->getUnits()->getTeamNames()[i];
            qsl << QString::fromStdString(aux2);
        }
    }

    avTeams.clear();

    loop = true;
    while (loop) {
        aux2 = QInputDialog::getItem(0, "Team selection", "Choose a team:", qsl, 0, false, &loop).toStdString();

        if (loop) {
            vector<string> v = board->getUnits()->getTeamNames();
            auto it1 = v.begin();
            auto it2 = v.end();
            vector<string>::iterator it = find(it1, it2, aux2);
            myTeam = distance(it1, it);
            loop = !client->initializeClient(myTeam);
            if (loop) {
                delete client;
                client = new Client(aux);
                promptMessage("Error: team selected not available");
            }
        } else {
            delete client;
            return;
        }
    }
    okFlag = true;
    client->setTeam(myTeam);
    promptMessage("Connection established");
}

void UIGame::hostInit() {
    okFlag = false;
    isHost = true;
    bool loop = true;
    string aux;

    QStringList qsl;
    for (string str : board->getUnits()->getTeamNames()) {
        qsl << QString::fromStdString(str);
    }

    aux = QInputDialog::getItem(0, "Team selection", "Choose a team:", qsl, 0, false, &loop).toStdString();

    vector<string> v = board->getUnits()->getTeamNames();
    auto it1 = v.begin();
    auto it2 = v.end();
    vector<string>::iterator it = find(it1, it2, aux);
    myTeam = distance(it1, it);

    host = new Host(board->getUnits()->getTeams(), myTeam, SocketHelper::getIP(), board->getUnits()->getMapIdentifier());
    host->close();
}

UIBoard *UIGame::getBoard()
{
    return board;
}

BGColor UIGame::getBG(int x, int y)
{
    return board->getUIMap(x,y)->getBg();
}

FGColor UIGame::getFG(int x, int y)
{
    return board->getUIMap(x,y)->getFg();
}

BorderColor UIGame::getBorder(int x, int y)
{
    return board->getUIMap(x,y)->getBorder();
}

char UIGame::getIcon(int x, int y)
{
    if (board->getUnits()->getUMap(x, y) != nullptr) {
        return board->getUnits()->getUMap(x, y)->getIcon();
    } else {
        return ' ';
    }
}

float UIGame::getHealth(int x, int y)
{
    if (board->getUnits()->getUMap(x, y) != nullptr) {
        return (board->getUnits()->getUMap(x, y)->getCHealth()/board->getUnits()->getUMap(x, y)->getHealth());
    } else {
        return 0;
    }
}

void UIGame::hostGame1() {
    board = new UIBoard();
    board->loadMap1();
    hostInit();
    board->initUI(myTeam);
}

void UIGame::joinGame1() {
    board = new UIBoard();
    board->loadMap1();
    clientInit();
    board->initUI(myTeam);
}

void UIGame::hostGameCastleAssault() {
    board = new UIBoard();
    board->loadCastleAssault();
    hostInit();
    board->initUI(myTeam);
}

void UIGame::joinGameCastleAssault() {
    board = new UIBoard();
    board->loadCastleAssault();
    clientInit();
    board->initUI(myTeam);
}

void UIGame::promptMessage(string s) {
    QMessageBox ErrDialog;
    ErrDialog.setText(QString::fromStdString(s));
    ErrDialog.exec();
}

void UIGame::advanceTurn() {
    turn++;
    board->getUnits()->advanceTurn();
}
