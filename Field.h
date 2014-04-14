#ifndef FIELD_H
#define FIELD_H

class Field
{
public:
    Field(unsigned char = 0, unsigned char = 0, char = 0, char = 0);
    unsigned char getRow(void) const;
    void setRow(unsigned char);
    unsigned char getColumn(void) const;
    void setColumn(unsigned char);
    char getOldValue(void) const;
    void setOldValue(char);
    char getNewValue(void) const;
    void setNewValue(char);

private:
    unsigned char row;
    unsigned char column;
    char oldValue;
    char newValue;
};

#endif
