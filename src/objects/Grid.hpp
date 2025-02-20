#pragma once

#include <unordered_set>
#include <vector>
#include "core/object/GameObject.hpp"
#include "common/Vector2.hpp"

enum class PLAY_STATE
{
	PAUSE,
	PLAY
};

enum class EDIT_STATE
{
	MOVE,
	DRAW,
	ERASE
};

// Has the alive cells data, updates and renders them, moves grid
class Grid : public GameObject
{
private:
	Vector2<float> position = { 0, 0 };
	double genTimePassed = 0.0f; // Counting time till genTimePassed > genInterval
	
	std::unordered_set<Vector2<int>, Vector2<int>::Hash> aliveCells;

	void UpdateGridState();
	void DrawRect();
	void EraseRect();
	void UpdateGridMovement();
	void ClearGrid();
	Vector2<float> lastGridPos = { 0, 0 };
	Vector2<float> lastMousePos = { 0, 0 };

	void UpdateGeneration();
	std::vector<Vector2<int>> NeighborPositions(const Vector2<int> cell);

public:
	Grid();
	~Grid() = default;

	void Render(Renderer* renderer) override;
	void Update() override;

	struct GridModifiable
	{
		float zoomIn = 30;
		Vector2<float> clampZoomIn = { 5, 70 };
		float genInterval = 0.1f; // Interval between generation updates in seconds
		SDL_Color rectColor = SDL_Color{ 200, 200, 200, 255 };
		PLAY_STATE playState = PLAY_STATE::PAUSE;
		EDIT_STATE editState = EDIT_STATE::MOVE;
	};
	GridModifiable modifiable;
};