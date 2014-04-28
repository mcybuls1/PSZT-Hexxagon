#include "Field.h"

Field::Field(unsigned char row, unsigned char column, char oldV, char newV)
{
    this->row = row;
    this->column = column;
    oldValue = oldV;
    newValue = newV;
}

char Field::getRow(void) const
{
    return row;
}

void Field::setRow(char newRow)
{
    row = newRow;
}

char Field::getColumn(void) const
{
    return column;
}

void Field::setColumn(char newColumn)
{
    column = newColumn;
}

char Field::getOldValue(void) const
{
    return oldValue;
}

void Field::setOldValue(char ov)
{
    oldValue = ov;
}

char Field::getNewValue(void) const
{
    return newValue;
}

void Field::setNewValue(char nv)
{
    newValue = nv;
}
