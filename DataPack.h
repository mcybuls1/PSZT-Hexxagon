#ifndef DATAPACK_H
#define DATAPACK_H

#include "Field.h"
#include <utility>

class DataPack
{
public:
    DataPack(char, const std::pair<Field, Field>&);
    char getActionCode(void) const;
    std::pair<Field, Field> getChange(void) const;

private:
    char actionCode;
    std::pair<Field, Field> change;

};

#endif
