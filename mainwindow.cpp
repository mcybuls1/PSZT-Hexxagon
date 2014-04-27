#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fielditem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Ustawienie sceny
    ui->setupUi(this);
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 975, 635);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setBackgroundBrush(QBrush(QColor(255,255,153)));

    qDebug() << ui->graphicsView->frameSize();

    //Polaczenie slotow
    connect(ui->actionZako_cz, SIGNAL(triggered()), qApp , SLOT(quit()));
    connect(ui->actionNowa_Gra, SIGNAL(triggered()), this , SLOT(startGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    scene->clear();
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= i; ++j) {
            FieldItem *item = new FieldItem();
            item->setPos(460 - i * 60 + j * 120, i * 30);
            scene->addItem(item);
        }

    }

    for (int i = 0; i < 9; ++i) {
        if(i % 2 == 0){
            for (int j = 0; j < 4; ++j) {
                FieldItem *item = new FieldItem();
                item->setPos(460 - 3 * 60 + j * 120, (i + 5) * 30);
                scene->addItem(item);
            }
        } else {
            for (int j = 0; j < 5; ++j) {
                FieldItem *item = new FieldItem();
                item->setPos(460 - 4 * 60 + j * 120, (i + 5) * 30);
                scene->addItem(item);
            }
        }
    }

    for (int i = 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            FieldItem *item = new FieldItem();
            item->setPos(460 - i * 60 + j * 120, (16 - i) * 30);
            scene->addItem(item);
        }
    }

}





