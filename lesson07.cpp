/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

int main(int argc, char ** argv)
{

	const char * error = TTF_GetError();
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font,
		"Welcome to Programmer's Ranch", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,
		surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
*/