#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include "Renderer.hpp"
#include "core/object/GameObject.hpp"
#include "objects/Grid.hpp"
#include "imgui/ImGuiManager.hpp"

#define MAX_FPS 144

class GameOfLife
{
private:
	SDL_Window* window = nullptr;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<ImGuiManager> imguiManager;

	std::vector<GameObject*> objects;

	void Update();
	void Render();

	bool gameRunning = true;

public:
	GameOfLife();
	~GameOfLife();

	void MainLoop();
};