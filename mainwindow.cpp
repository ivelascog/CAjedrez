#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    g = new UIGame();
    g->joinGame1();
    ui->setupUi(this);
    int h = g->getBoard()->getUnits()->getHeight();
    int w = g->getBoard()->getUnits()->getWidth();
    g->getBoard()->getUnits()->getArmies(1)->actionReset();
    g->getBoard()->getUnits()->getArmies(0)->actionReset();
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
    ui->healthBar->setFormat("%v/%m");

    QSizePolicy sp_retain = ui->unitStats_2->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->unitStats_2->setSizePolicy(sp_retain);
    QSizePolicy cp_retain = ui->confirmPanel->sizePolicy();
    cp_retain.setRetainSizeWhenHidden(true);
    ui->confirmPanel->setSizePolicy(cp_retain);
    QSizePolicy ap_retain = ui->attackPreviewWidget->sizePolicy();
    ap_retain.setRetainSizeWhenHidden(true);
    ui->attackPreviewWidget->setSizePolicy(ap_retain);
    ui->unitStats_2->hide();
    ui->confirmPanel->hide();
    ui->attackPreviewWidget->hide();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(toggleOpacity()));

    walkTimer = new QTimer(this);
    connect(walkTimer, SIGNAL(timeout()), this, SLOT(walkAnim()));

    colorButtons();
}

MainWindow::~MainWindow()
{
    for (vector<QPushButton *> v : buttonMap) {
        v.clear();
    }
    buttonMap.clear();

    blinkingButtons.clear();

    buttonsOriginal.clear();

    delete ui;
    delete timer;
    delete g;
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
                    backgroundColor = "background-color: rgb(255, 255, 100);";
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
    if(tilesAreActive) {
        if (g->getBG(x, y) == inMoveRange) {
            moveSelectedUnit(x, y);
        } else if (g->getBG(x, y) == inAttackRangeandHostile && g->getBoard()->inRange(selectedUnit)[x][y] > 0) {
            previewAttack(x,y);
        } else {
            selectedUnit = g->getBoard()->getUnits()->getUMap(x, y);
            if (selectedUnit != nullptr) {
                displayUnitStats(selectedUnit);
            } else {
                ui->unitStats_2->hide();
            }
            g->getBoard()->updateButtonLogic(x, y);
        }
        colorButtons();
    }
}

void MainWindow::moveSelectedUnit(int x, int y)
{
    path = g->getBoard()->walk(selectedUnit, x, y);

    tilesAreActive = false;
    moveExhaust = 0;
    walkTimer->start(300);
}

void MainWindow::walkAnim()
{
    int x2 = path.top()[0];
    int y2 = path.top()[1];
    if (path.size() == 1) {
        g->getBoard()->getUnits()->move(selectedUnit->getPosX(), selectedUnit->getPosY(), x2, y2);
    } else {
        g->getBoard()->getUnits()->forceMove(selectedUnit->getPosX(), selectedUnit->getPosY(), x2, y2);
    }
    g->getBoard()->updateButtonLogic(selectedUnit->getPosX(), selectedUnit->getPosY(), moveExhaust);
    moveExhaust += 1;
    path.pop();
    colorButtons();
    if(path.empty()) {
        walkTimer->stop();
        tilesAreActive = true;
        g->getBoard()->updateButtonLogic(selectedUnit->getPosX(), selectedUnit->getPosY());
        colorButtons();
    }
}

void MainWindow::toggleOpacity()
{
    if (grow) {
        opacity += 20;
        if (opacity >= 255) {
            opacity = 255;
            grow = false;
        }
    } else {
        opacity -= 20;
        if (opacity <= 0) {
            opacity = 0;
            grow = true;
        }
    }

    QPalette falete = ui->resultPreviewHealth->palette();
    QColor color = falete.color(QPalette::Window);
    color.setAlpha(opacity);
    falete.setColor(QPalette::Window, color);
    color = falete.color(QPalette::Highlight);
    color.setAlpha(opacity);
    falete.setColor(QPalette::Highlight, color);
    color = falete.color(QPalette::Text);
    color.setAlpha(opacity);
    falete.setColor(QPalette::Text, color);
    color = falete.color(QPalette::Base);
    color.setAlpha(opacity);
    falete.setColor(QPalette::Base, color);
    ui->resultPreviewHealth->setPalette(falete);

    for (int i = 0; i < blinkingButtons.size(); i++) {
        blinkingButtons[i]->setStyleSheet(buttonsOriginal[i] + QString::fromStdString("border:" + to_string(opacity/70 + 1) + "px solid; border-color: rgb(200, 200, 200);border-radius: 4px;"));
    }
}

void MainWindow::displayUnitStats(Unit *u) {
    ui->unitStats_2->hide();
    ui->attack->setText(QString::fromStdString(to_string(u->getDamage())));
    ui->move->setText(QString::fromStdString(to_string(u->getMovm())));
    ui->range->setText(QString::fromStdString(to_string(u->getRange())));
    ui->healthBar->setMaximum(u->getHealth());
    ui->healthBar->setValue(u->getCHealth());
    colorBar(ui->healthBar);
    ui->name->setText(QString::fromStdString(u->getName() + " " + to_string(u->getId()) + " / Team " + to_string(u->getTeam())));
    ui->portrait->setStyleSheet(QString::fromStdString("border-image:url(:/unitIcons/" + u->getIconName() + ".jpg);"));
    ui->unitStats_2->show();
}

void MainWindow::previewAttack(int x, int y)
{
    tilesAreActive = false;
    Unit *u = g->getBoard()->getUnits()->getUMap(x,y);
    ui->previewName->setText(QString::fromStdString(u->getName() + " " + to_string(u->getId()) + ": "));
    ui->currentPreviewHealth->setMaximum(u->getHealth());
    ui->currentPreviewHealth->setValue(u->getCHealth());
    ui->resultPreviewHealth->setMaximum(u->getHealth());
    ui->resultPreviewHealth->setValue(u->getCHealth() - selectedUnit->getDamage());
    colorBar(ui->currentPreviewHealth);
    colorBar(ui->resultPreviewHealth);
    ui->attackPreviewWidget->show();
    blinkingButtons.push_back(buttonMap[x][y]);
    buttonsOriginal.push_back(buttonMap[x][y]->styleSheet());
    timer->start(40);
    ui->confirmPanel->show();
    targetedUnit = g->getBoard()->getUnits()->getUMap(x,y);
}

void MainWindow::colorBar(QProgressBar *bar)
{
    QPalette falete = bar->palette();
    float f = (float) bar->value()/ (float) bar->maximum();
    QColor color;
    if (f > 0.5) {
        falete.setColor(QPalette::Highlight, Qt::green);
    } else if (f <= (float) 1/5) {
        falete.setColor(QPalette::Highlight, Qt::red);
    } else {
        falete.setColor(QPalette::Highlight, Qt::yellow);
    }
    bar->setPalette(falete);
}

void MainWindow::on_confirm_clicked()
{
    g->getBoard()->getUnits()->attack(selectedUnit, targetedUnit);
    g->getBoard()->updateButtonLogic(selectedUnit->getPosX(), selectedUnit->getPosY());
    g->getBoard()->getUnits()->massRemoveComplete();
    ui->confirmPanel->hide();
    ui->attackPreviewWidget->hide();
    timer->stop();
    colorButtons();
    blinkingButtons.clear();
    buttonsOriginal.clear();
    targetedUnit = nullptr;
    tilesAreActive = true;
}

void MainWindow::on_cancel_clicked()
{
    ui->confirmPanel->hide();
    ui->attackPreviewWidget->hide();
    timer->stop();
    colorButtons();
    blinkingButtons.clear();
    buttonsOriginal.clear();
    targetedUnit = nullptr;
    tilesAreActive = true;
}
