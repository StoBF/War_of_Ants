#ifndef LABEL_H
#define LABEL_H


#include <sstream>
#include "graphics.h"

class Label
{
	
public:
    Label( Graphics *graph, TTF_Font *font, double x, double y, Color col, const std::string &string = "");
	Label(Graphics *graph, TTF_Font *font, double x, double y, Color col, const double lvl);
    ~Label();

    void draw();
    void setX( int x );
    int getX() const;
    void setY( int y );
    int getY() const;
    void setXY( int x, int y );
    int getHeight();
    int getWidth();
    const SDL_Rect& getRect();
    std::string getText();

    Label &setText(const std::string& string );

    template<typename T>
    Label& operator <<( const T& t );

private:
    void createTexture();
    void calculateRects();

    Graphics *graphics;
    TTF_Font *font_;
    Color color;
    std::stringstream content;
	std::stringstream xp;
    SDL_Surface *surface,
							*TEXT;
    SDL_Texture *texture,
							*sec_texture;
    SDL_Rect sourceRect, targetRect;
};

template< typename T >
Label& Label::operator <<(const T &t)
{
    content << t;
    createTexture();
    return *this;
}

#endif // LABEL_H
