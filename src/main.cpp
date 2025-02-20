#include <SDL3/SDL.h>
#include <stdio.h>

#include "core/GameOfLife.hpp"

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Failed SDL_Init() -> %s", SDL_GetError());
		return -1;
	}

	GameOfLife* app = new GameOfLife();
	app->MainLoop();

	delete app;

	return 0;
}