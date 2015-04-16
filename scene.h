#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "food.h"
#include "block.h"
#include "colony.h"
#include "graphics.h"


class Scene
{
public:
    Scene( Graphics *gr, double w, double h );
    virtual ~Scene();

    std::vector< Block * > food;
    std::vector< Colony * > colonies;
	int mouseX, mouseY;
    int fieldWidth, fieldHeight;
    bool quit;
    Graphics *graphics;
    Color foodColor;
    double FPS;

    void init();

    virtual void draw();
    void allFoods();
    virtual void processEvents();
    virtual void action();

    void forgetFood( Food *what );
    void forgetColony( Colony *what );
private:
    bool dying;
};

#endif // SCENE_H
