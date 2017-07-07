#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    UIGame *g = new UIGame();
    g->joinGame1();
    ui->setupUi(this);
    int h = g->getBoard()->getUnits()->getHeight();
    int w = g->getBoard()->getUnits()->getWidth();
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++){
            auto button = new QPushButton();
            if (g->getBoard()->getUnits()->getUMap(i,j) != nullptr) {
                char c = g->getBoard()->getUnits()->getUMap(i,j)->getIcon();
                button->setText(&c);
            } else {
                button->setText("");
            }

            if (g->getBoard())

            if (g->getBoard()->getTerrain()->getTMap(i,j)->isObstacle()) {
                button->setStyleSheet("background-color: rgb(102, 102, 0);");
            }
            button->setFixedHeight(40);
            button->setFixedWidth(40);
            ui->BoardUI->addWidget(button, j, i);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
