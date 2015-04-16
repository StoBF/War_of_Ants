#ifndef FOOD_H
#define FOOD_H

#include "block.h"

class Food : public Block
{
public:
    Food( const std::string& name );
    virtual ~Food();
    virtual void draw();
	virtual void print();
private:
};

#endif // FOOD_H
