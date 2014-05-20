#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    //Inicjacja tablicy z polami
    for(unsigned char i = 0; i < Model::N_ROWS; ++i)
    {
        for(unsigned char j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j] = new FieldItem(Model::EMPTY);
        }
    }

    board[3][4]->setState(Model::FORBIDDEN);
    board[4][3]->setState(Model::FORBIDDEN);
    board[5][5]->setState(Model::FORBIDDEN);
    board[0][0]->setState(Model::RED);
    board[8][4]->setState(Model::RED);
    board[4][8]->setState(Model::RED);
    board[4][0]->setState(Model::BLUE);
    board[0][4]->setState(Model::BLUE);
    board[8][8]->setState(Model::BLUE);

    for(unsigned char i = 0; i < Model::N_ROWS/2; ++i)
    {
        for(unsigned char j = Model::N_COLUMNS/2 + 1 + i; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setState(Model::FORBIDDEN);
            board[j][i]->setState(Model::FORBIDDEN);
        }
    }
}

void MainWindow::gameOver(unsigned char gs)
{

}

void MainWindow::update(std::vector<Field> changedFields, unsigned char reds, unsigned char blues)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    scene->clear();
    //Zmien rysowanie tak zeby rysowalo wzgledem tego co masz na pulpicie i wykorzystywalo FORBIDDEN
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= i; ++j) {
            FieldItem *item = new FieldItem(Model::EMPTY);
            item->setPos(460 - i * 60 + j * 120, i * 30);
            scene->addItem(item);
        }

    }

    for (int i = 0; i < 9; ++i) {
        if(i % 2 == 0){
            for (int j = 0; j < 4; ++j) {
                FieldItem *item = new FieldItem(Model::EMPTY);
                item->setPos(460 - 3 * 60 + j * 120, (i + 5) * 30);
                scene->addItem(item);
            }
        } else {
            for (int j = 0; j < 5; ++j) {
                FieldItem *item = new FieldItem(Model::EMPTY);
                item->setPos(460 - 4 * 60 + j * 120, (i + 5) * 30);
                scene->addItem(item);
            }
        }
    }

    for (int i = 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            FieldItem *item = new FieldItem(Model::EMPTY);
            item->setPos(460 - i * 60 + j * 120, (16 - i) * 30);
            scene->addItem(item);
        }
    }

}





