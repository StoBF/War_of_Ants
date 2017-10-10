#include "scene.h"
#include "colony.h"
#include "food.h"
#include "ant.h"
#include "graphics.h"


#include <SDL2/SDL.h>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

Scene *Block::mainScene;

Scene::Scene(Graphics *gr, double w, double h) :
fieldWidth(w),
fieldHeight(h),
quit(false),
graphics(gr),
foodColor(ColorBlue),
FPS(0.0),
dying(false)
{
    Block::mainScene = this;
    Colony *red   = new Colony( this, ColorRed  , 440, 10 ),
           *black = new Colony( this, ColorBlack,  15, 10 );
    new Base( 15,  15, "Red", red );
    new Base( FIELD_WIDTH - 15, FIELD_HEIGHT - 15, "Black", black);
    std::stringstream name;
    for(int i=0;i<OBJECTS;++i)
    {
        name.str( "" );
        name << "Ant_" << i;
        new Ant( rand() % 31 - 15 + black->bases[0]->getX(),
                 rand() % 31 - 15 + black->bases[0]->getY(),
                 name.str(),
                 black, gr,i );
        new Ant( rand() % 31 - 15 + red->bases[0]->getX(),
                 rand() % 31 - 15 + red->bases[0]->getY(),
                 name.str(),
                 red, gr,i);
        name.str( "" );
        name << "Food_" << i;
        new Food( name.str() );
    }
}


Scene::~Scene()
{
  dying = true;
  for( int i = food.size() - 1; i >= 0; --i )
      delete food[i];
  for( int i = colonies.size() - 1; i >= 0; --i )
      delete colonies[i];
}

void Scene::forgetFood( Food *what )
{
    SDL_assert( what != NULL );
    std::string name = what->getName();
    food.erase( std::remove( food.begin(), food.end(), what ), food.end() );
    if( !dying )
        new Food( name );
}

void Scene::forgetColony(Colony *what)
{
    SDL_assert( what != NULL );
    colonies.erase( std::remove( colonies.begin(), colonies.end(), what ), colonies.end() );
}

void Scene::processEvents()
{
    SDL_Event Event;
	SDL_GetMouseState(&mouseX, &mouseY);
    while( SDL_PollEvent( &Event ) )
    {
        switch( Event.type )
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch( Event.key.keysym.scancode )
            {
            case SDL_SCANCODE_Z:
                allFoods();
                break;
			case SDL_SCANCODE_Q:
				system("clr");
				for (unsigned int colonyNum = 0; colonyNum < colonies.size(); ++colonyNum)
				{
					cout << colonies[colonyNum] << ' ' << colonies[colonyNum]->score << endl;
					for (unsigned int antNum = 0; antNum < colonies[colonyNum]->ants.size(); ++antNum)
					{
						
						colonies[colonyNum]->ants[antNum]->print();
					}

				}
				for (int i = 0; i < 20; ++i)
				{
					cout << food[i]->getName() << " " << food[i]->weight << endl;
				}
				break;
            case SDL_SCANCODE_M:
                SDL_assert(false);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Scene::action()
{
    for( unsigned int colonyNum = 0; colonyNum < colonies.size(); ++colonyNum )
    {
        for( unsigned int antNum = 0; antNum < colonies[colonyNum]->ants.size(); ++antNum )
        {
            colonies[colonyNum]->ants[antNum]->action();
        }
    }
}

void Scene::draw()
{
	char xmouse[4], ymouse[4];
	std::stringstream ss1, ss2;
	ss1 << mouseX;
	ss2 << mouseY;
	ss1 << xmouse;
	ss2 << ymouse;
    graphics->setColor( ColorYellow );
	graphics->setColor_sec(ColorYellow);
    int result = SDL_RenderClear( graphics->renderer );
	int result_sec = SDL_RenderClear(graphics->sec_renderer);
    SDL_assert( result >= 0 );
	SDL_assert(result_sec >= 0);
    for(unsigned int i=0;i<colonies.size();++i)
    {
        colonies[i]->draw();
    }
    for (unsigned int i=0;i<food.size();i++)
    {
        food[i]->draw();
    }
    SDL_RenderPresent( graphics->renderer );
	SDL_RenderPresent(graphics->sec_renderer);
}

void Scene::allFoods()
{
    for ( unsigned int i = 0; i < food.size(); ++i )
    {
        delete food[i];
    }

}
