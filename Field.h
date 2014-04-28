#ifndef FIELD_H
#define FIELD_H

class Field
{
public:
    Field(unsigned char = 0, unsigned char = 0, char = 0, char = 0);
    char getRow(void) const;
    void setRow(char);
    char getColumn(void) const;
    void setColumn(char);
    char getOldValue(void) const;
    void setOldValue(char);
    char getNewValue(void) const;
    void setNewValue(char);

private:
    char row;
    char column;
    char oldValue;
    char newValue;
};

#endif
