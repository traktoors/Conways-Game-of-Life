#include "InfoWindow.hpp"
#include "core/EventManager.hpp"
#include <iostream>

InfoWindow::InfoWindow() {
	ImGui::SetNextWindowSize(ImVec2(100, 500));
}

InfoWindow::~InfoWindow()
{
	delete gridMod;
}

// Only one of checkboxes can be selected and one needs to be checked
void HandleCheckBoxes(bool* states, Uint8 selected, size_t size)
{
	memset(states, 0, size);
	states[selected] = true;
}

void InfoWindow::WindowData()
{
	HandleCheckBoxes(editStateCheckB, static_cast<Uint8>(gridMod->editState), 3);
	HandleCheckBoxes(playStateCheckB, static_cast<Uint8>(gridMod->playState), 2);

	ImGui::Begin("Inspector");

	if (ImGui::BeginTabBar(""))
	{
		if (ImGui::BeginTabItem("About"))
		{
			ImGui::PushTextWrapPos(ImGui::GetWindowSize().x);
			ImGui::Text("Conway's Game of Life have pretty simple rules:\n* A live cell survives if it has 2 or 3 neighbors. If it has fewer than 2, it dies from underpopulation, and if it has more than 3, it dies from overpopulation.\n* A dead cell becomes alive if it has exactly 3 living neighbors.");
			ImGui::PopTextWrapPos();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Controls"))
		{
			ImGui::Text("Keyboard Controls");
			ImGui::Text("\"D\" -> Draw");
			ImGui::Text("\"E\" -> Erase");
			ImGui::Text("\"M\" -> Move");
			ImGui::Text("\"P\" -> Play");
			ImGui::Text("\"O\" -> Pause");
			ImGui::Text("\"C\" -> Clear");
			ImGui::Text("\"F\" -> Next Generation");

			ImGui::Text("\n\nEdit State");
			if (ImGui::Checkbox("Move", &editStateCheckB[0]))
			{
				gridMod->editState = EDIT_STATE::MOVE;
			}
			if (ImGui::Checkbox("Draw", &editStateCheckB[1]))
			{
				gridMod->editState = EDIT_STATE::DRAW;
			}
			if (ImGui::Checkbox("Erase", &editStateCheckB[2]))
			{
				gridMod->editState = EDIT_STATE::ERASE;
			}

			ImGui::Text("\n\nGame State");
			if (ImGui::Checkbox("Pause", &playStateCheckB[0]))
			{
				//HandleCheckBoxes(playStateCheckB, 0, 2);
				gridMod->playState = PLAY_STATE::PAUSE;
			}
			if (ImGui::Checkbox("Play", &playStateCheckB[1]))
			{
				//HandleCheckBoxes(playStateCheckB, 1, 2);
				gridMod->playState = PLAY_STATE::PLAY;
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Parameters"))
		{
			ImGui::Text("Zoom In");
			ImGui::SliderFloat("-", &gridMod->zoomIn, gridMod->clampZoomIn.x, gridMod->clampZoomIn.y, "%.2f");

			ImGui::Text("Interval between generations");
			ImGui::SliderFloat(".", &gridMod->genInterval, 0.01f, 5.0f, "%.2f");

			ImGui::Text("Rect color");
			ImGui::ColorEdit3(",", (float*)&_rectColor);
			gridMod->rectColor.r = Uint8(_rectColor.x * 255);
			gridMod->rectColor.g = Uint8(_rectColor.y * 255);
			gridMod->rectColor.b = Uint8(_rectColor.z * 255);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Presets"))
		{


			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	EventManager::GetInstance().Getimgfo(ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered());

	ImGui::End();
}