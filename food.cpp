#include "food.h"
#include "block.h"
#include "scene.h"
#include "graphics.h"
#include <iostream>
using std::cout;
using std::endl;

Food::Food(const std::string &name ) :
    Block( rand() % mainScene->fieldWidth, rand() % mainScene->fieldHeight, name )
	//label(getApp()->getGraphics()->smallFont,
	//location,
	//App::getApp()->getScene()->foodColor,
	//name)
{
	weight = 300.0;
    SDL_Point realPoint = mainScene->graphics->point( getX(), getY() );
    mainScene->food.push_back( this );
}

Food::~Food()
{
    mainScene->forgetFood( this );
}
void Food::print()
{
	cout << getName() << ' ' << weight << endl;
}
void Food::draw()
{
    mainScene->graphics->setColor( mainScene->foodColor );
    SDL_Rect rect = Graphics::rect( getX(), getY(), 1.3, 1.3 );
    SDL_RenderDrawRect( mainScene->graphics->renderer, &rect );
}
