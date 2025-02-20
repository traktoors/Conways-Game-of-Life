#pragma once

#include <SDL3/SDL.h>

class Renderer
{
private:
	SDL_Renderer* renderer = nullptr;
public:
	Renderer(SDL_Renderer* renderer);
	~Renderer();
	void RenderClear(SDL_Color clearColor);
	void RenderPresent();

	void FillRect(float posX, float posY, float width, float height, SDL_Color rectColor);
	/*
	* zoomIn is basically cell size in pixels, for example, cell size = 20 = zoomIn
	* Positions are for illusion that grid is moving
	* Grid is drawn on the whole window!
	*/
	void DrawGrid(float posX, float posY, float zoomIn, SDL_Color lineColor);
};