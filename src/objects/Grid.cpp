#include <unordered_map>
#include "Grid.hpp"
#include "common/colors.hpp"
#include "core/EventManager.hpp"
#include "common/math.hpp"
#include "common/time.hpp"

Grid::Grid() {}

void Grid::Update()
{
	UpdateGridState();

	if (!EventManager::GetInstance().IsImGuiWindowHovered())
	{
		if (modifiable.editState == EDIT_STATE::MOVE)
			UpdateGridMovement();

		else if (modifiable.editState == EDIT_STATE::DRAW)
			DrawRect();

		else // EDIT_STATE::ERASE
			EraseRect();
	}

	if (modifiable.playState == PLAY_STATE::PLAY)
	{
		genTimePassed += Time::GetInstance().GetDelta();
		if (genTimePassed >= modifiable.genInterval)
		{
			UpdateGeneration();
			genTimePassed = 0;
		}
	}
	
}

void Grid::UpdateGridMovement()
{
	if (EventManager::GetInstance().IsMouseButtonPressed(SDL_BUTTON_LEFT))
	{
		lastGridPos = position;
		EventManager::GetInstance().GetMousePosition(lastMousePos.x, lastMousePos.y);
	}

	if (EventManager::GetInstance().IsMouseButtonHeld(SDL_BUTTON_LEFT))
	{
		Vector2<float> mousePos;
		EventManager::GetInstance().GetMousePosition(mousePos.x, mousePos.y);

		position = Vector2<float>(lastGridPos.x + (mousePos.x - lastMousePos.x), lastGridPos.y + (mousePos.y - lastMousePos.y));
	}

	modifiable.zoomIn += EventManager::GetInstance().GetMouseScrollVertical();
	Math::ClampF(modifiable.zoomIn, modifiable.clampZoomIn.x, modifiable.clampZoomIn.y);
}

void Grid::ClearGrid()
{
	aliveCells.clear();
}

void Grid::EraseRect()
{
	if (EventManager::GetInstance().IsMouseButtonHeld(SDL_BUTTON_LEFT))
	{
		float mouseX, mouseY;
		EventManager::GetInstance().GetMousePosition(mouseX, mouseY);


		int posX = int((mouseX - position.x) / modifiable.zoomIn);
		int posY = int((mouseY - position.y) / modifiable.zoomIn);
		Vector2<int> cell(posX, posY);

		if (aliveCells.find(cell) != aliveCells.end())
			aliveCells.erase(cell);
	}
}

void Grid::DrawRect()
{
	if (EventManager::GetInstance().IsMouseButtonHeld(SDL_BUTTON_LEFT))
	{
		float mouseX, mouseY;
		EventManager::GetInstance().GetMousePosition(mouseX, mouseY);

		int posX = int((mouseX - position.x) / modifiable.zoomIn);
		int posY = int((mouseY - position.y) / modifiable.zoomIn);

		aliveCells.insert(Vector2<int>(posX, posY));
	}
}

std::vector<Vector2<int>> Grid::NeighborPositions(const Vector2<int> cell)
{
	std::vector<Vector2<int>> neighbors;
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0) continue;

			neighbors.push_back(Vector2<int>(cell.x + dx, cell.y + dy));
		}
	}

	return neighbors;
}

void Grid::UpdateGeneration()
{
	std::unordered_set<Vector2<int>, Vector2<int>::Hash> newAliveCells;
	std::unordered_map<Vector2<int>, int, Vector2<int>::Hash> neighborCounts;	// neighboring cells and how much alive cells are around them

	for (const Vector2<int>& cell : aliveCells)
		for (const Vector2<int>& pos : NeighborPositions(cell))
			neighborCounts[pos]++;

	for (const auto& cell : neighborCounts)
	{
		if (aliveCells.find(cell.first) != aliveCells.end())	// If cell is alive
		{
			if (cell.second == 2 || cell.second == 3)
				newAliveCells.insert(cell.first);
		}

		else	// if cell is dead
		{
			if(cell.second == 3)
				newAliveCells.insert(cell.first);
		}
	}

	aliveCells = std::move(newAliveCells);
}

void Grid::Render(Renderer* renderer)
{
	renderer->DrawGrid(position.x, position.y, modifiable.zoomIn, Colors::lineColor);

	for (auto cell : aliveCells)
		renderer->FillRect(	float(cell.x) * modifiable.zoomIn + position.x,
							float(cell.y) * modifiable.zoomIn + position.y,
							modifiable.zoomIn,
							modifiable.zoomIn,
							modifiable.rectColor);
}

void Grid::UpdateGridState()
{
	switch (EventManager::GetInstance().GetLastKeyPressed())
	{
	case SDL_SCANCODE_P:
		modifiable.playState = PLAY_STATE::PLAY;
		break;

	case SDL_SCANCODE_O:
		modifiable.playState = PLAY_STATE::PAUSE;
		break;

	case SDL_SCANCODE_D:
		modifiable.editState = EDIT_STATE::DRAW;
		break;

	case SDL_SCANCODE_E:
		modifiable.editState = EDIT_STATE::ERASE;
		break;

	case SDL_SCANCODE_M:
		modifiable.editState = EDIT_STATE::MOVE;
		break;

	case SDL_SCANCODE_C:
		modifiable.playState = PLAY_STATE::PAUSE;
		ClearGrid();
		break;

	case SDL_SCANCODE_F:
		UpdateGeneration();
		break;
	}
}