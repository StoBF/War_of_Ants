#ifndef COLONY_H
#define COLONY_H

#include <vector>

#include "block.h"
#include "graphics.h"


class Base;
class Scene;
class Ant;

class Colony
{
public:
    Colony(Scene* scene, Color col, double scoreX, double scoreY );
    virtual ~Colony();

    Scene* mainScene;
    double score;
	double warehouse;
    Color color;
    double scorePosX, scorePosY;
    std::vector< Block * > bases;
    std::vector< Ant * > ants;
	virtual void by_ant();
    virtual void draw();
    virtual void forgetBase( Block *what );
    virtual void forgetAnt( Block *what );
};

#endif // COLONY_H
