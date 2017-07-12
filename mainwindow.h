#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UI/UIGame.h"
#include <QPushButton>

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
private:
    Ui::MainWindow *ui;
    void clientSetUp(UIGame *g);
    vector<vector<QPushButton *>> buttonMap;
    UIGame * g;
private slots:
    void tileClicked(int x, int y);
};

#endif // MAINWINDOW_H
