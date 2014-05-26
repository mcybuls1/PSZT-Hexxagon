#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Model;
class GameScene;

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "Field.h"
#include <vector>
#include "gamescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void gameOver(unsigned char gs);
    void update(std::vector<Field> changedFields, unsigned char reds, unsigned char blues);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameScene *scene;


protected slots:
    void startGame();

};

#endif // MAINWINDOW_H
