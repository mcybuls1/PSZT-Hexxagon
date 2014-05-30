#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Ustawienie sceny
    ui->setupUi(this);
    scene = new GameScene(ui->graphicsView);
    scene->setSceneRect(0, 0, 975, 635);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setBackgroundBrush(QBrush(QColor(255,204,153)));

    //qDebug() << ui->graphicsView->frameSize();

    //Polaczenie slotow
    connect(ui->actionZako_cz, SIGNAL(triggered()), qApp , SLOT(quit()));
    connect(ui->actionNowa_Gra, SIGNAL(triggered()), this , SLOT(startGame()));

}

void MainWindow::gameOver(unsigned char gs)
{

}

void MainWindow::update(std::vector<Field> changedFields, unsigned char reds, unsigned char blues)
{
//    scene->updateFields(changedFields, reds, blues);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    scene->newGame();
}





