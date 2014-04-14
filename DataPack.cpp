#include "DataPack.h"
#include "Field.h"
#include <utility>

using namespace std;

DataPack::DataPack(char code, const pair<Field, Field>& p) : actionCode(code), change(p)
{
}

char DataPack::getActionCode(void) const
{
    return actionCode;
}

pair<Field,Field> DataPack::getChange(void) const
{
    return change;
}
