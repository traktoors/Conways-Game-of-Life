#include "GameOfLife.hpp"
#include "EventManager.hpp"

#include "common/Vector2.hpp"
#include "common/colors.hpp"
#include "common/time.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include "gui/InfoWindow.hpp"

GameOfLife::GameOfLife()
{
	// Setup SDL_Window and SDL_Renderer graphics context
	window = SDL_CreateWindow("Conway's Game Of Life", 1280, 720, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* _renderer = SDL_CreateRenderer(window, nullptr);
	renderer = std::make_unique<Renderer>(_renderer);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL3_InitForSDLRenderer(window, _renderer);
	ImGui_ImplSDLRenderer3_Init(_renderer);

	// Setting up ImGui windows
	imguiManager = std::make_unique<ImGuiManager>();

	Grid* grid = new Grid();
	objects.push_back(grid);

	InfoWindow* infoWindow = new InfoWindow();
	infoWindow->gridMod = &grid->modifiable;
	imguiManager->AddWindow(infoWindow);

	SDL_ShowWindow(window);
}

void GameOfLife::MainLoop()
{
	Uint64 frameStart, frameEnd;

	while (gameRunning)
	{
		frameStart = SDL_GetTicks();
		Time::GetInstance().Update();

		EventManager::GetInstance().PollEvents();

		if (EventManager::GetInstance().ShouldQuit())
			gameRunning = false;

		Update();
		Render();


		// roughly capping fps to MAX_FPS
		frameEnd = SDL_GetTicks() - frameStart;
		if (frameEnd < 1000 / MAX_FPS)
		{
			SDL_Delay(Uint32((1000 / MAX_FPS) - frameEnd));
		}
	}
}

void GameOfLife::Update()
{
	for (GameObject* object : objects)
	{
		object->Update();
	}
}

void GameOfLife::Render()
{
	imguiManager->RenderWindows();

	renderer->RenderClear(Colors::clearColor);

	for (GameObject* object : objects)
	{
		object->Render(renderer.get());
	}

	renderer->RenderPresent();
}

GameOfLife::~GameOfLife()
{
	// Cleanup
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(window);
	SDL_Quit();
}