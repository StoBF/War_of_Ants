#include "block.h"
#include "scene.h"
#include "graphics.h"
#include <cmath>
#include <algorithm>

Block::Block(double x, double y, const std::string &name) :
x_(x), y_(y), name_(name), Invent(false)
{
	for (int i = 0; i < 3; ++i) {
		bool* space = new bool[i];
		//space[i] = true;
	}
}

Block::~Block()
{
}

void Block::setX( double x )
{
    x_ = x;
}
double Block::getX() const
{
    return x_;
}

void Block::setY( double y )
{
    y_ = y;
}

double Block::getY() const
{
    return y_;
}

void Block::setXY(double x, double y)
{
    x_ = x;
    y_ = y;
}
void Block::setInvent(bool i)
{
	Invent = i;
}
bool Block::getInvent()
{
	return Invent;
}

const std::string &Block::getName() const
{
    return name_;
}

void Block::setName(const std::string &newName)
{
    name_ = newName;
}

double Block::distance(Block* target) const
{
    double deltaX = getX() - target->getX();
    double deltaY = getY() - target->getY();
    double delta = ((deltaX*deltaX)+(deltaY*deltaY));
    SDL_assert( delta>= 0);
    return sqrt(delta);
}
void Block::step(Direction where,double a)
{
    SDL_assert( ( first <= where ) && ( where <= last ) );
    switch (where){
    case up :
        y_=(y_+a);
        if(y_ >= mainScene->fieldHeight)
            y_ -= mainScene->fieldHeight;
        break;
    case down :
        y_=(y_-a);
        if(y_ < 0)
            y_ += mainScene->fieldHeight;
        break;
    case left :
        x_=(x_-a);
        if(x_ < 0)
           x_ += mainScene->fieldWidth;
        break;
    case right :
        x_=(x_+a);
        if(x_ >= mainScene->fieldWidth)
            x_ -= mainScene->fieldWidth;
        break;
	case up_left:
		y_ = (y_ + a / 2);
		x_ = (x_ - a / 2);
		if (y_ >= mainScene->fieldHeight)
			y_ -= mainScene->fieldHeight;
		break;
	case down_left:
		y_ = (y_ - a / 2);
		x_ = (x_ - a / 2);
		if (y_ < 0)
			y_++;//= mainScene->fieldHeight;
		break;
	case down_right:
		y_ = (y_ - a/2);
		x_ = (x_ + a/2);
		if (x_ < 0)
			x_++;//+;= mainScene->fieldWidth;
		break;
	case up_right:
		y_ = (y_ + a / 2);
		x_ = (x_ + a / 2);
		if (x_ >= mainScene->fieldWidth)
			x_ -= mainScene->fieldWidth;
		break;
	case stay:
		x_ = x_;
		y_ = y_;
		break;
    case end :
        break;
    default:
        SDL_assert( false );
        break;
    }
}

bool Block::isOn( Block** target,
                  const std::vector<Block*> *reserve)
{
    SDL_assert( target != NULL );
    SDL_assert( reserve != NULL );
    if( *target == NULL )
        return false;
    std::vector<Block*>::const_iterator existingTarget
                                    = std::find( reserve->begin(),
                                                 reserve->end(),
                                                 *target );
    if( existingTarget == reserve->end() )
        return false;
    if( isOn( *existingTarget) )
        return true;
    return false;
}

bool Block::isOn(Block* target) //const
{
	if (target == NULL)
		return false;
	else
	{
		//if ((x_ == target->x_) && (y_ == target->y_))
			if (distance(target)<=1.0)
		{
			return true;
		}
		else
			return false;
	}
}

void Block::set_weight_add(double s)
{
	weight += s;

}
void Block::set_weight_take(double s)
{
	weight -= s;

}


Block* Block::nearest( const std::vector<Block*>& vect )
{
	int a = 0;
	double Mem[20];
	for (int i = 0; i < 20; ++i)
	{
		Mem[i] = 0;
	}
	double minDistance=0;
    if( vect.size() == 0 )
    {
        return NULL;
    }
    Block* nearest = vect[0];
	if (vect.size() > 1)
	{		
		
		for (int i = 0; i < vect.size(); ++i)
		{
			minDistance = distance(nearest);
		}
		for (unsigned int i = 1; i < vect.size(); ++i)
		{
			double current = distance(vect[i]);
			if (current < minDistance)
			{
				Mem[i] = minDistance;
				minDistance = current;
				nearest = vect[i];
			}

		}
	}
        
	for (int i = 0; i < 3; ++i)
	{
		if (nearest->space[i])
		{
			a++;
		}
	}

	if (a == 0)
				for (int i = 0; i < 20; ++i)
				{
					if (Mem[i] != 0) {
						if ((Mem[i] > minDistance) && (Mem[i] < minDistance + 120))
						{
							minDistance = Mem[i];
							nearest = vect[i];
						}
					}
				}
    
    return nearest;
}
