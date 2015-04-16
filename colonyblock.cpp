#include "colonyblock.h"
#include "colony.h"

ColonyBlock::ColonyBlock( double x, double y, const std::string& name, Colony *col ) :
    Block( x, y, name ), colony( col )
{
}

ColonyBlock::~ColonyBlock()
{
}

Colony *ColonyBlock::getColony() const
{
    return colony;
}
