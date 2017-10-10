#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define FIELD_WIDTH   400
#define FIELD_HEIGHT  200
#define BLOCK_SIZE    3
#define HEADER_SIZE   50
#define WINDOW_WIDTH  ( BLOCK_SIZE * (FIELD_WIDTH)  )
#define WINDOW_HEIGHT ( HEADER_SIZE + ( BLOCK_SIZE * FIELD_HEIGHT ) )
#define OBJECTS       20

struct Color : public SDL_Color
{
    Color( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255 );
};

class Graphics
{
public:
    Graphics(const char *title, int width, int height);
    ~Graphics();
    static SDL_Point point( float x, float y );
    static SDL_Rect rect( float x, float y, float w , float h );
    void setColor( const Color &color );
	void setColor_sec(const Color &color);

    int error;

    SDL_Window *window, *sec_window;
    SDL_Renderer *renderer, *sec_renderer;
    TTF_Font *font,
             *smallFont;
};



const Color ColorBlack      ( 0, 0, 0 ),
            ColorRed        ( 255, 0, 0),
            ColorBlue       ( 0, 0, 255 ),
            ColorYellow     ( 255, 255, 128 ),
            ColorGreen      ( 0, 255, 0 );


#endif // GRAPHICS_H
