#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Model;

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "fielditem.h"
#include "Field.h"
#include "model.h"
#include <vector>

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
    QGraphicsScene *scene;
    FieldItem *board[9][9];
    Model* model;

protected slots:
    void startGame();

};

#endif // MAINWINDOW_H
