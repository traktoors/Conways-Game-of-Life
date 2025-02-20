#pragma once

#include "core/Renderer.hpp"

class GameObject
{
public:
	GameObject() {}
	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;
};