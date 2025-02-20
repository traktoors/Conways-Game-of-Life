#pragma once

#include <vector>
#include "ImGuiWindow.hpp"

class ImGuiManager
{
private:
	std::vector<ImGuiWindow*> windows;

public:
	ImGuiManager();
	~ImGuiManager();

	void AddWindow(ImGuiWindow* window);
	void RenderWindows();
};