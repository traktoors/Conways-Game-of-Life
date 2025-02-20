#include "Renderer.hpp"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"
#include <iostream>
#include <cmath>

Renderer::Renderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Renderer::RenderClear(SDL_Color clearColor)
{
	SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	SDL_RenderClear(renderer);
}

void Renderer::RenderPresent()
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
	SDL_RenderPresent(renderer);
}

void Renderer::DrawGrid(float posX, float posY, float zoomIn, SDL_Color lineColor)
{
	int width, height;
	SDL_GetRenderOutputSize(renderer, &width, &height);

	SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, lineColor.a);
	for (float x = fmod(posX, zoomIn); x <= width; x += zoomIn)		// Vertical
	{
		SDL_RenderLine(renderer, x, 0, x, float(height));
	}
	for (float y = fmod(posY, zoomIn); y <= height; y += zoomIn)	// Horizontal
	{
		SDL_RenderLine(renderer, 0, y, float(width), y);
	}
}

void Renderer::FillRect(float posX, float posY, float width, float height, SDL_Color rectColor)
{
	SDL_FRect rect{ posX, posY, width, height };
	SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
	SDL_RenderFillRect(renderer, &rect);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}