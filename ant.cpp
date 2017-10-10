#include "ant.h"
#include "scene.h"

//#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;

Ant::Ant(double x, double y, const std::string& name, Colony *col, Graphics *gr, int pt) :
ColonyBlock(x, y, name, col),
direction(stay),
state(sitHome),
target(NULL),
Name(name),
dosome(NULL),
color(col->color),
Level(1.0),
XP(0.0001),
Pos(pt),
	my_space (0),
	grap(gr)
{

	Spead = DRand2(0.8, 0.1);
	weight = DRand2(1.3, 0.3);
	range = DRand2(130.0, 90.0);
	for (int i = 0; i < 6; ++i)
	{
		double* bag = new double[i];
		Memory[i] = NULL;
	}
	//createLable();
	SDL_assert( col != NULL );
    getColony()->ants.push_back( this );
}

void Ant::info(double inf)
{
	//label->operator<<(XP);
}

void Ant::createLable()
{
	int N = 10;
	for (int i = 0; i < 3; ++i) {
		if (this->color.r)
		{
			
			if (i == 0) {
				int  pos = 0;
				int a =15;
				pos =(a * Pos);
				label[i] = new Label(grap, grap->smallFont, 5, pos, color, getName());
			}
			if (i == 1) {
				int  pos = 0;
				int a = 15;
				pos = 8 + (a * Pos);
				label[i] = new Label(grap, grap->smallFont, 5, pos, color, Level);
			}
			if (i == 2) {
				int  pos = 0;
				int a = 15;
				pos = 8 + (a * Pos);
				label[i] = new Label(grap, grap->smallFont, 15, pos, color, XP);
			}
		}
		else
		{
			if (i == 0) {
				int  pos = 0;
				int a = 15;
				pos = (a * Pos);
				label[i] = new Label(grap, grap->smallFont, 150, pos + 10, color, getName());
			}
			if (i == 1) {
				int  pos = 0;
				int a = 15;
				pos = 8 + (a * Pos);
				label[i] = new Label(grap, grap->smallFont, 150 + 10, pos + 10, color, Level);
			}
			if (i == 2) {
				int  pos = 0;
				int a = 15;
				pos = 8 + (a * Pos);
				label[i] = new Label(grap, grap->smallFont, 150 + 20, pos + 10, color, XP);
			}
		}
	}
}

void Ant::set_xp(double a)
{
	XP = a / (Level/10);
	if (XP >= 1.0)
	{
		Level++;
		XP -= 1.0;
	}
}

void Ant::set_bag_add(double s)
{	
	bag[0] += s;
}
void Ant::set_bag_take(double s)
{
	bag[0] -= s;
}
double Ant::get_bag(int i)
{
	return bag[i];
}
double Ant::DRand2(double a, double b) {								//генерує вагу яку може перенести юніт 
	return a + static_cast<double>(std::rand()) / RAND_MAX*(b - a);
}


Ant::~Ant()
{
    getColony()->forgetAnt( this );
}

void Ant::turnTo(Block *target)
{
    SDL_assert( target != NULL );
    if ( (getY()<target->getY() ) && ((getX()) == target->getX()) && ( direction != Block::down ) )
    {
        direction = Block::up;
    }
    else if ( (getY()>target->getY()) && ((getX()) == target->getX()) && (direction != Block::up) )
    {
        direction = Block::down;
    }
    else if ( (getX()<target->getX()) && ((getY()) == target->getY()) && (direction != Block::up))
    {
        direction = Block::right;
    }
    else if ( (getX()>target->getX()) && ((getY()) == target->getY()) && (direction != Block::right) )
    {
        direction = Block::left;
    }
	else if ((getY()<target->getY()) && ((getX())>target->getX()) && (direction != Block::down))
	{
		direction = Block::up_left;
	}
	else if ((getY()>target->getY()) && ((getX())>target->getX()) && (direction != Block::up))
	{
		direction = Block::down_left;
	}
	else if (((getY())<target->getY()) && (getX()<target->getX()) &&  (direction != Block::left))
	{
		direction = Block::up_right;
	}
	else if ((getY()>target->getY()) && (getX()<target->getX())  &&  (direction != Block::right))
	{
		direction = Block::down_right;
	}
	else
	{
		direction = Block::stay;
	}
}

void Ant::action()
{

	
	switch (state)
	{
	case sitHome:
			    //target = nearest(getColony()->bases);
				state = idle;
				break;
				
	case idle:
		target = nearest(mainScene->food);
		if (distance(target) <= range)
		{
					state = goingToFood;
					break;		
		}
		
		else
		{
			state = sitHome;
			break;
		}

	case goingToFood:
			if (isOn(&target, &mainScene->food))
			{
				if (target->weight <= 0.0)
				{					
					delete target;
				}
				if (!target)
				{
					state = sitHome;
				}
				if ((bag[0] < weight) && (!dosome))
				{
					for (size_t i = 0; i < 3; i++)
					{
						if (target->space[i]) {
							target->space[i] = false;
							dosome = true;
							my_space = i;
							break;						

						}
						if (i == 2) {
							state = idle;
							target = NULL;
						}
					}
				}
					if ((bag[0] < weight) && (dosome))
					{
						target->set_weight_take(weight / 99);
						set_bag_add(weight / 99);
						break;
					}

					if ((bag[0] > weight))
					{
						if (dosome){
							dosome = false;
							target->space[my_space] = true;
							my_space = 0;

							target = nearest(getColony()->bases);
							Invent = true;
							state = carringFoodHome;
						}
						break;
				}
			}
			break;


	case carringFoodHome://несемо їжу в колонію
		if (isOn(&target, &getColony()->bases))
		{
			if (Invent == true)
			{
				if (bag[0] > 0.0) {
					dosome = true;
					getColony()->warehouse += (weight / 99);
					set_bag_take(weight / 99 );

				}
				else
				{
					dosome = false;
					getColony()->score++;
					if (getColony()->score >= 50)
					{
						getColony()->by_ant();
						getColony()->score -= 50;

					}
					set_xp(weight);
					Invent = false;
					state = idle;
					target = NULL;
				}
			}
		}
		break;

	default:
		SDL_assert(false);
		break;
		}
		if (target)
			turnTo(target);

		step(direction, Spead);
		
		

}

void Ant::print()
{
	cout << getName()<<' '<<weight<<" bag "<<bag[0] << '  '<< state<<" XP "<<XP<<" Lvl "<<Level<<" SP "<<Spead<<endl;
}
void Ant::draw()
{
	
	createLable();
    mainScene->graphics->setColor( getColony()->color );
	for (int i = 0; i < 3; ++i)
	{
		label[i]->draw();
	}
	if (Invent)
	{
		SDL_Rect rect = Graphics::rect(getX(), getY(), 1.5, 1.5);
		SDL_RenderDrawRect(mainScene->graphics->renderer, &rect);
		SDL_Point realPoint = mainScene->graphics->point(getX(), getY());
	}
	else
	{
		SDL_Rect rect = Graphics::rect(getX(), getY(), 0.9, 0.9);
		SDL_RenderDrawRect(mainScene->graphics->renderer, &rect);
		SDL_Point realPoint = mainScene->graphics->point(getX(), getY());
	}
	for (int i = 0; i < 3; ++i)
	{
		label[i]->~Label();
	}
}
