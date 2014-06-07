#include "gamescene.h"
#include <QMessageBox>
//#include <QString>

GameScene::GameScene(QGraphicsView *view, QObject *parent) :
    QGraphicsScene(parent)
{
    //Inicjacja tablicy z polami
    for(unsigned char i = 0; i < Model::N_ROWS; ++i)
    {
        for(unsigned char j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j] = new FieldItem(Model::EMPTY);
            board[i][j]->setRow(i);
            board[i][j]->setColumn(j);
        }
    }

    started = false;
    model->setView(this);
    model = new Model();
    this->view = view;

    //s
    computer = false;
}

void GameScene::newGame()
{
    char** boardGiven = model->reset();

    if(!started)
    {
        this->addSimpleText("Reds", QFont("Times", 16, QFont::Bold));
        this->addSimpleText("Blues", QFont("Times", 16, QFont::Bold))->moveBy(930, 0);

        redScore = this->addSimpleText(QString::number((int)model->getReds()), QFont("Times", 16, QFont::Bold));
        redScore->moveBy(0, 20);

        blueScore = this->addSimpleText(QString::number((int)model->getBlues()), QFont("Times", 16, QFont::Bold));
        blueScore->moveBy(930, 20);
    }
    else
    {
        redScore->setText(QString::number((int)model->getReds()));
        blueScore->setText(QString::number((int)model->getBlues()));
    }

    for (int i = 0; i < Model::N_ROWS; ++i)
    {
        for (int j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setState(boardGiven[i][j]);
            if(board[i][j]->getState() != Model::FORBIDDEN)
            {
                board[i][j]->setPos( 220 + 60 * j, 130 + 60 * i - 30 * j);
                if(!started)
                {
                this->addItem(board[i][j]);
                }
            }
        }
    }

    clearSelections();
    started = true;
}

void GameScene::clearSelections()
{
    for (int i = 0; i < Model::N_ROWS; ++i)
    {
        for (int j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setSelection(FieldItem::NONE);
        }
    }
    from = NULL;
    view->viewport()->update();
}

FieldItem* GameScene::getField(int i, int j)
{
    return board[i][j];
}

void GameScene::update(std::vector<Field> changedFields, unsigned char reds, unsigned char blues)
{
//    for (unsigned int i = 0; i < changedFields.size(); ++i)
//    {
//       Field field = changedFields[i];
//       qDebug() << field.getNewValue();
//       board[(int)field.getRow()][(int)field.getColumn()]->setState(field.getNewValue());
//    }
//    view->viewport()->update();
}

void GameScene::gameOver(unsigned char gs)
{
    //
}

void GameScene::checkGameState()
{
    char state = model->getGameState();

    if(state == Model::LASTING)
    {
        return;
    }
    else if(state == Model::LOST)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Przegrałeś!");
        msgBox.setInformativeText("Czy chcesz rozpocząć nową grę?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
            newGame();
    }
    else if(state == Model::WON)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Wygrałeś!");
        msgBox.setInformativeText("Czy chcesz rozpocząć nową grę?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
            newGame();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Remis!");
        msgBox.setInformativeText("Czy chcesz rozpocząć nową grę?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
            newGame();
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(selectedItems().size() == 0)
    {
        return;
    }
    FieldItem* selected = (FieldItem*)selectedItems().back();

    if(selected->getSelection() == FieldItem::NONE)
    {
        clearSelections();

        if(!model->isClickable((Field)*selected))
        {
            return;
        }

        selected->setSelection(FieldItem::SELECTED);
        from = selected;

        std::pair<std::vector<Field>, std::vector<Field> > response = model->getAvailbleFields((Field)*selected);

        foreach (Field field, response.first)
        {
            board[(int)field.getRow()][(int)field.getColumn()]->setSelection(FieldItem::CLONEABLE);
        }

        foreach (Field field, response.second)
        {
            board[(int)field.getRow()][(int)field.getColumn()]->setSelection(FieldItem::MOVABLE);
        }

    }
    else if(selected->getSelection() == FieldItem::SELECTED)
    {
        clearSelections();
    }
    else if(selected->getSelection() == FieldItem::CLONEABLE)
    {

        model->playerAction(Model::CLONE, std::make_pair<Field, Field> ((Field)*from, (Field)*selected));
        selected->setState(Model::RED);
        clearSelections();
        computer = true;
    }
    else if(selected->getSelection() == FieldItem::MOVABLE)
    {
        model->playerAction(Model::MOVE, std::make_pair<Field, Field> ((Field)*from, (Field)*selected));
        selected->setState(Model::RED);
        from->setState(Model::EMPTY);
        clearSelections();
        computer = true;
    }

    //Zsynchronizowanie stanu z modelem
    for (int i = 0; i < Model::N_ROWS; ++i)
    {
        for (int j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setState(model->getBoard()[i][j]);
        }
    }

    checkGameState();
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mouseReleaseEvent(event);
    checkGameState();
    if(computer)
    {
        //QThread::sleep(1);
        model->computerAction();
        //Zsynchronizowanie stanu z modelem
        for (int i = 0; i < Model::N_ROWS; ++i)
        {
            for (int j = 0; j < Model::N_COLUMNS; ++j)
            {
                board[i][j]->setState(model->getBoard()[i][j]);
            }
        }
        redScore->setText(QString::number((int)model->getReds()));
        blueScore->setText(QString::number((int)model->getBlues()));

        computer = false;
    }

}
