#ifndef BASE_H
#define BASE_H

#include "colonyblock.h"

class Colony;

class Base : public ColonyBlock
{
public:
    Base(double x, double y, const std::string &name,  Colony *col );
    virtual ~Base();
    virtual void draw();

private:

};

#endif // BASE_H
