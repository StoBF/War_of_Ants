#ifndef ANT_H
#define ANT_H

#include "colonyblock.h"
#include "colony.h"
#include "base.h"
#include "food.h"
#include "label.h"
#include "graphics.h"

class Ant : public ColonyBlock
{
public:
    Ant(double x, double y, const std::string &name, Colony* col, Graphics *gr, int pt);

    virtual ~Ant();
	bool dosome;// індикатор виконнання певних дій
	int my_space;	
    virtual void draw();
	Graphics *grap;
	virtual void turnTo( Block *target );
    virtual void action();
	inline void info(double inf);
	virtual void set_bag_add(double s);
	virtual void set_bag_take(double s);
	//virtual void set_Lvl(double xp);
	virtual void set_xp(double xp);
	virtual double get_bag(int i);
	virtual double DRand2(double a, double b);
	virtual void createLable();
    enum State {sitHome, idle, goingToFood, carringFoodHome};
	void print();
	Label *label[3];
	Color color;

private:
    Block::Direction direction;
    State state;
	Block *target;
	Block * Memory[6];
	std::string Name;
	int Pos;
	double Level;
	double XP;
	double Spead;
	double range;
	double bag[6];
	


};
#endif // ANT_H
