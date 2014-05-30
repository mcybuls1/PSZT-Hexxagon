#include "gamescene.h"

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

    model = new Model();
    this->view = view;
}

void GameScene::newGame()
{
    char** boardGiven = model->reset();
    for (int i = 0; i < Model::N_ROWS; ++i)
    {
        for (int j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setState(boardGiven[i][j]);
            if(board[i][j]->getState() != Model::FORBIDDEN)
            {
                board[i][j]->setPos( 220 + 60 * j, 130 + 60 * i - 30 * j);
                this->addItem(board[i][j]);
            }
        }
    }
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

void GameScene::updateFields(std::vector<Field> changedFields, unsigned char reds, unsigned char blues)
{
//    for (int i = 0; i < changedFields.size(); ++i)
//    {
//       Field field = changedFields[i];
//       qDebug() << field.getNewValue();
//       board[(int)field.getRow()][(int)field.getColumn()]->setState(field.getNewValue());
//    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(selectedItems().size() == 0)
    {
        return;
    }
    FieldItem* selected = (FieldItem*)selectedItems().back();
    //selected->setSelection(FieldItem::SELECTED);

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
            //            qDebug() << (int)field.getRow();
        }

    }
    else if(selected->getSelection() == FieldItem::SELECTED)
    {
        clearSelections();
    }
    else if(selected->getSelection() == FieldItem::CLONEABLE)
    {
        model->action(Model::CLONE, std::make_pair<Field, Field> ((Field)*from, (Field)*selected));
        selected->setState(Model::RED);
        clearSelections();
    }
    else if(selected->getSelection() == FieldItem::MOVABLE)
    {
        model->action(Model::MOVE, std::make_pair<Field, Field> ((Field)*from, (Field)*selected));
        selected->setState(Model::RED);
        from->setState(Model::EMPTY);
        clearSelections();
    }
    //Zsynchronizowanie stanu z modelem
    for (int i = 0; i < Model::N_ROWS; ++i)
    {
        for (int j = 0; j < Model::N_COLUMNS; ++j)
        {
            board[i][j]->setState(model->getBoard()[i][j]);
        }
    }

    view->viewport()->update();
}
