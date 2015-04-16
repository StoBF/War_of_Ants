#include <vector>
#include <string>

#ifndef BLOCK_H
#define BLOCK_H

class Scene;

class Block {
public:
    static Scene *mainScene;

    Block( double x, double y, const std::string& name );
    virtual ~Block();
	bool Invent;
	double weight;
	bool space[3];
    void setX(double x );
    double getX() const;
    void setY(double y );
    double getY() const;
    void setXY(double x, double y );

	void setInvent(bool i);
	bool getInvent();
    const std::string& getName() const;
    void setName( const std::string& newName );
    virtual void draw() = 0;
    double distance(Block* target) const;

    enum Direction{ first, up = first, down, left, right, up_left, down_left, up_right, down_right, stay, end, last = end} ;
    void step(Direction where,double a); //'a' ןנטילא÷ למהטפ³ךאעמנ םא רגטהך³סעü
	bool isOn(Block* target); //const;
    bool isOn( Block** target,
               const std::vector<Block*> *reserve = 0);
	void set_weight_add(double s);
	void set_weight_take(double s);

    Block* nearest( const std::vector<Block*>& vect );

private:
    double x_;
    double y_;

    std::string name_;
};

#endif // BLOCK_H
