#include "graphics.h"

Graphics::Graphics( const char *title, int width, int height ) :
    error( 0 ),
    window( NULL ),
    renderer( NULL )
{
    int initResult = SDL_Init( SDL_INIT_VIDEO );
    SDL_assert( initResult >= 0 );

    window = SDL_CreateWindow( title,
                               310, 5,
                               width, height,
                               0 );
	sec_window = SDL_CreateWindow(title,
		5, 5,
		300, WINDOW_HEIGHT,
		0);

    SDL_assert( window != NULL );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_assert( renderer != NULL );

	sec_renderer = SDL_CreateRenderer(sec_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_assert(sec_renderer != NULL);

    int ttfInitResult = TTF_Init();
    SDL_assert( ttfInitResult >= 0 );

    font = TTF_OpenFont("times.ttf", 24);
    SDL_assert( font != NULL );

	const char * error = TTF_GetError();

    smallFont = TTF_OpenFont("times.ttf", 8);
    SDL_assert( font != NULL );
	
}

Graphics::~Graphics()
{
    TTF_Quit();
    SDL_Quit();
}

SDL_Point Graphics::point( float x, float y )
{
    SDL_Point transformed;
    transformed.x = x * BLOCK_SIZE;
    transformed.y = HEADER_SIZE + y * BLOCK_SIZE;
    return transformed;
}

SDL_Rect Graphics::rect( float x, float y, float w, float h )
{
    SDL_Rect transformed;
    transformed.x = x * BLOCK_SIZE;
    transformed.y = HEADER_SIZE + y * BLOCK_SIZE;
    transformed.w = w * BLOCK_SIZE;
    transformed.h = h * BLOCK_SIZE;
    return transformed;
}

void Graphics::setColor( const Color &color )
{
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );

}

void Graphics::setColor_sec(const Color &color)
{
	SDL_SetRenderDrawColor(sec_renderer, color.r, color.g, color.b, color.a);
}

Color::Color( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha )
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
