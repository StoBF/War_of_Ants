#include "colony.h"

#include <sstream>
#include <algorithm>

#include "ant.h"
#include "scene.h"
#include "base.h"

Colony::Colony( Scene * scene, Color col, double scoreX, double scoreY ) :
    mainScene( scene ),
    score( 0.0 ),
    color( col ),
    scorePosX( scoreX ),
    scorePosY( scoreY ),
	warehouse(10.0)
{
    SDL_assert( mainScene != NULL );
    mainScene->colonies.push_back( this );
}

void Colony::by_ant()
{
	if (color.r) {
		int i = ants.size();
		std::stringstream name;
		name.str("");
		name << "Ant_" << i;
		new Ant(scorePosX-400, scorePosY, name.str(), this, mainScene->graphics, i);
	}
	else
	{
		int i = ants.size();
		std::stringstream name;
		name.str("");
		name << "Ant_" << i;
		new Ant(scorePosX - 400, scorePosY+200, name.str(), this, mainScene->graphics, i);
	}
}

Colony::~Colony()
{
    for(int i = ants.size() - 1; i >= 0; --i)
    {
        delete ants[i];
    }
    SDL_assert( ants.size() == 0 );
    for(int i = bases.size() - 1; i >= 0; --i)
    {
        delete bases[i];
    }
    SDL_assert( bases.size() == 0 );
    mainScene->forgetColony( this );
}

void Colony::draw()
{
    for(unsigned int i=0;i<bases.size();++i)
    {
        bases[i]->draw();
    }
    for(unsigned int i=0;i<ants.size();++i)
    {
        ants[i]->draw();
    }
   
}

void Colony::forgetBase(Block *what)
{
    SDL_assert( what != NULL );
    bases.erase( std::remove( bases.begin(), bases.end(), what ), bases.end() );
}

void Colony::forgetAnt(Block *what)
{
    SDL_assert( what != NULL );
    ants.erase( std::remove( ants.begin(), ants.end(), what ), ants.end() );
}
