#include "base.h"
#include "colony.h"
#include "scene.h"

Base::Base(double x, double y, const std::string& name, Colony *col ) :
    ColonyBlock( x, y, name, col )
{
    SDL_assert( col != NULL );
    getColony()->bases.push_back( this );
}

Base::~Base()
{
    getColony()->forgetBase( this );
}


void Base::draw()
{
    mainScene->graphics->setColor( getColony()->color );
    SDL_Point points[5];
    points[0] = Graphics::point( getX() + 4, getY()     );
    points[1] = Graphics::point( getX(),     getY() + 4 );
    points[2] = Graphics::point( getX() - 4, getY()     );
    points[3] = Graphics::point( getX(),     getY() - 4 );
    points[4] = points[0];
    SDL_RenderDrawLines( mainScene->graphics->renderer, points, 5 );
}

