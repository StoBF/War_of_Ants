#ifndef COLONYBLOCK_H
#define COLONYBLOCK_H

#include "block.h"
class Colony;

class ColonyBlock : public Block
{
public:
    ColonyBlock(double x, double y, const std::string &name, Colony *col);
    virtual ~ColonyBlock();
    
    Colony *getColony() const;
    virtual void draw() = 0;

private:
    Colony *colony;
};

#endif // COLONYBLOCK_H
