#include "ImGuiManager.hpp"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_sdl3.h"

ImGuiManager::ImGuiManager() {}

ImGuiManager::~ImGuiManager()
{
	for(ImGuiWindow* window : windows)
	{
		delete window;
	}
}

void ImGuiManager::AddWindow(ImGuiWindow* window)
{
	windows.push_back(window);
}

void ImGuiManager::RenderWindows()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	for (ImGuiWindow* window : windows)
	{
		window->WindowData();
	}

	ImGui::Render();
}