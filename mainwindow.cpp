#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    g = new UIGame();
    g->joinGameCastleAssault();
    ui->setupUi(this);/**/
    g->getBoard()->getUnits()->getArmies(0)->actionReset();
    g->getBoard()->getUnits()->getArmies(1)->actionReset();
    g->getBoard()->getUnits()->getArmies(2)->actionReset();
   // g->getBoard()->getUnits()->forceMove(7, 9, 7, 3); //*/
    int h = g->getBoard()->getUnits()->getHeight();
    int w = g->getBoard()->getUnits()->getWidth();
    buttonMap = vector<vector<QPushButton *>> ((unsigned long) w, vector<QPushButton *> ((unsigned long) h));
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++){
            buttonMap[i][j] = new QPushButton();
            buttonMap[i][j]->setFixedHeight(40);
            buttonMap[i][j]->setFixedWidth(40);
            QObject::connect(buttonMap[i][j], &QPushButton::released, [=] { tileClicked(i, j); });
            ui->BoardUI->addWidget(buttonMap[i][j], j, i);
        }
    }
    g->getBoard()->updateButtonLogic();
    colorButtons();
}

MainWindow::~MainWindow()
{
    for (vector<QPushButton *> v : buttonMap) {
        v.clear();
    }
    buttonMap.clear();
    delete ui;
}

void MainWindow::colorButtons() {
    int h = g->getBoard()->getUnits()->getHeight();
    int w = g->getBoard()->getUnits()->getWidth();
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++){
            QString backgroundColor;
            QString foregroundColor;
            QString borderColor;
            char c = g->getIcon(i, j);
            string s;
            s.push_back(c);
            auto qst = QString::fromStdString(s);
            switch (g->getBG(i, j)) {
                case obstacle:
                    backgroundColor = "background-color: rgb(102, 102, 0);";
                    break;
                case def:
                    backgroundColor = "background-color: rgb(255, 255, 255);";
                    break;
                case inAttackRange:
                    backgroundColor = "background-color: rgba(255, 0, 0, 0);";
                    break;
                case inAttackRangeandHostile:
                    backgroundColor = "background-color: rgb(120, 0, 0);";
                    break;
                case inMoveRange:
                    backgroundColor = "background-color: rgb(100, 255, 100);";
                    break;
                case selected:
                    backgroundColor = "background-color: rgb(255, 255, 150);";
                    break;
                default:
                    backgroundColor = "background-color: rgb(255, 255, 0);";
                    break;
            }

            switch (g->getFG(i, j)) {
                case white:
                    foregroundColor = "color: rgb(255, 255, 255);";
                    break;
                case enemy:
                    foregroundColor = "color: rgb(200, 0, 0);";
                    break;
                case me:
                    foregroundColor = "color: rgb(0, 150, 0);";
                    break;
                case ally:
                    foregroundColor = "color: rgb(0, 0, 150);";
                    break;
                default:
                    foregroundColor = "color: rgb(150, 150, 150);";
                    break;
            }

            switch (g->getBorder(i, j)) {
                case posToDefendAlly:
                    borderColor = "border:2px solid; border-color: rgb(0, 0, 150);";
                    break;
                case posToDefendEnemy:
                    borderColor = "border:2px solid; border-color: rgb(150, 0, 0);";
                    break;
                case posToDefendMe:
                    borderColor = "border:2px solid; border-color: rgb(0, 150, 0);";
                    break;
                case noBorder:
                    borderColor = "";
                    break;
                default:
                    borderColor = "border:4px solid; border-color: rgb(0, 255, 255);";
                    break;
            }

            buttonMap[i][j]->setText(qst);
            buttonMap[i][j]->setStyleSheet(backgroundColor + foregroundColor + borderColor);
        }
    }
}

void MainWindow::tileClicked(int x, int y)
{
    g->getBoard()->updateButtonLogic(x, y);
    colorButtons();
}
