#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UI/UIGame.h"
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void colorButtons();
    void displayUnitStats(Unit *u);
    void previewAttack(int x, int y);
    void colorBar(QProgressBar *bar);
    void moveSelectedUnit(int x, int y);
private:
    Unit *selectedUnit;
    Unit *targetedUnit;
    Ui::MainWindow *ui;
    void clientSetUp(UIGame *g);
    vector<vector<QPushButton *>> buttonMap;
    UIGame * g;
    QTimer * timer;
    QTimer * walkTimer;
    int opacity = 0;
    bool grow = true;
    bool tilesAreActive = true;
    vector<QPushButton *> blinkingButtons;
    vector<QString> buttonsOriginal;
    stack<array<int, 2>> path;
    bool aux;
    int moveExhaust;
private slots:
    void tileClicked(int x, int y);
    void toggleOpacity();
    void walkAnim();
    void on_confirm_clicked();
    void on_cancel_clicked();
};

#endif // MAINWINDOW_H
