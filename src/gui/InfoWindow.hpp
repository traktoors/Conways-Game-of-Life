#pragma once

#include "core/imgui/ImGuiWindow.hpp"
#include "common/Vector2.hpp"
#include <SDL3/SDL_pixels.h>
#include "objects/Grid.hpp"

class InfoWindow : public ImGuiWindow
{
private:
	ImVec4 _rectColor{200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f};

	bool editStateCheckB[3] = { true, false, false }; // Move, Draw, Erase
	bool playStateCheckB[2] = { true, false }; // Pause, Play
public:
	InfoWindow();
	~InfoWindow();
	void WindowData() override;

	// Grid data
	Grid::GridModifiable* gridMod = nullptr;
};