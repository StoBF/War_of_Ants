#include "label.h"

#include <cstring>

Label::Label(Graphics *graph, TTF_Font *font, double x, double y, Color col, const std::string& string) :
    graphics ( graph ),
    font_ ( font ),
    color( col ),
    surface( NULL ),
    texture( NULL ),
	sec_texture(NULL)
{
    SDL_assert( graph != NULL );
    if( string != "" )
    {
        content << string;
        createTexture();
        calculateRects();
   }
    else
    {
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = 0;
        sourceRect.h = 0;
        targetRect.h = 0;
        targetRect.w = 0;
    }
	
    targetRect.x = x;
    targetRect.y = y;
}

Label::Label(Graphics *graph, TTF_Font *font, double x, double y, Color col, const double lvl) :
graphics(graph),
font_(font),
color(col),
surface(NULL),
texture(NULL),
sec_texture(NULL)
{
	SDL_assert(graph != NULL);
	if (lvl!=NULL)
	{
		content << lvl;
		createTexture();
		calculateRects();
	}
	else
	{
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = 0;
		sourceRect.h = 0;
		targetRect.h = 0;
		targetRect.w = 0;
	}

	targetRect.x = x;
	targetRect.y = y;
}


Label::~Label()
{
    //if(TEXT)
        SDL_FreeSurface(TEXT);
    //if( sec_texture )
        SDL_DestroyTexture( sec_texture );
}

void Label::draw()
{
	createTexture();
    SDL_RenderCopy( graphics->sec_renderer, sec_texture, &sourceRect, &targetRect );
}

void Label::createTexture()
{
    if( TEXT != NULL )
    {
        SDL_FreeSurface( TEXT );
    }
    char buffer[256];
    strncpy_s( buffer, getText().c_str(), 256);
    TEXT = TTF_RenderText_Solid( font_, buffer, color );
    SDL_assert( TEXT != NULL );
   if( sec_texture != NULL)
    {
        SDL_DestroyTexture( sec_texture );
    }
	sec_texture = SDL_CreateTextureFromSurface(graphics->sec_renderer, TEXT);
    SDL_assert(sec_texture != NULL );

    SDL_GetClipRect( TEXT, &sourceRect );
    calculateRects();
}

void Label::calculateRects()
{
    SDL_GetClipRect( TEXT, &sourceRect );
    targetRect.w = sourceRect.w - sourceRect.x;
    targetRect.h = sourceRect.h - sourceRect.y;
}

const SDL_Rect& Label::getRect()
{
    return targetRect;
}

void Label::setX( int x )
{
    targetRect.x = x;
}

int Label::getX() const
{
    return targetRect.x;
}

void Label::setY( int y )
{
    targetRect.y = y;
}

int Label::getY() const
{
    return targetRect.y;
}

void Label::setXY( int x, int y )
{
    targetRect.x = x;
    targetRect.y = y;
}

int Label::getHeight()
{
    return targetRect.h;
}

int Label::getWidth()
{
    return targetRect.w;
}

std::string Label::getText()
{
    return content.str();
}

Label& Label::setText(const std::string &string)
{
    content.str( std::string(string) );
    content << string;
    createTexture();
    return *this;
}


