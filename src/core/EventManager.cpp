#include "EventManager.hpp"
#include "imgui_impl_sdl3.h"

EventManager& EventManager::GetInstance()
{
	static EventManager instance;
	return instance;
}

void EventManager::PollEvents()
{
	SDL_Event event;

	keyStatePrev = keyState;
	mouseButtonStatePrev = mouseButtonState;
	mouseMoved = false;
	mouseScrollVertical = 0;
	mouseScrollHorizontal = 0;
	lastKeyPressed = SDL_SCANCODE_UNKNOWN;

	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL3_ProcessEvent(&event);
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			shouldQuit = true;
			break;

		case SDL_EVENT_KEY_DOWN:
			keyState[event.key.scancode] = true;
			lastKeyPressed = event.key.scancode;
			break;

		case SDL_EVENT_KEY_UP:
			keyState[event.key.scancode] = false;
			break;

		case SDL_EVENT_MOUSE_MOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			mouseMoved = true;
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			mouseButtonState[event.button.button] = true;
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			mouseButtonState[event.button.button] = false;
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			mouseScrollHorizontal = event.wheel.x;
			mouseScrollVertical = event.wheel.y;
			break;

		default:
			OtherSDLEvents = event.type;
		}
	}
}

bool EventManager::ShouldQuit() const
{
	return shouldQuit;
}

//- - - - KEYBOARD EVENTS - - - -

bool EventManager::IsKeyPressed(SDL_Scancode key) const
{
	auto it1 = keyState.find(key);
	auto it2 = keyStatePrev.find(key);
	return it1 != keyState.end() && it1->second && (it2 == keyStatePrev.end() || !it2->second);
}

bool EventManager::IsKeyReleased(SDL_Scancode key) const
{
	auto it1 = keyState.find(key);
	auto it2 = keyStatePrev.find(key);
	return it1 != keyState.end() && !it1->second && (it2 != keyStatePrev.end() && it2->second);
}

bool EventManager::IsKeyHeld(SDL_Scancode key) const
{
	auto it = keyState.find(key);
	return it != keyState.end() && it->second;
}

SDL_Scancode EventManager::GetLastKeyPressed() const
{
	return lastKeyPressed;
}

//- - - - - - - -


//- - - - MOUSE EVENTS - - - -

bool EventManager::IsMouseButtonPressed(Uint8 button) const
{
	auto it1 = mouseButtonState.find(button);
	auto it2 = mouseButtonStatePrev.find(button);
	return it1 != mouseButtonState.end() && it1->second && (it2 == mouseButtonStatePrev.end() || !it2->second);
}

bool EventManager::IsMouseButtonReleased(Uint8 button) const
{
	auto it1 = mouseButtonState.find(button);
	auto it2 = mouseButtonStatePrev.find(button);
	return it1 != mouseButtonState.end() && !it1->second && (it2 != mouseButtonStatePrev.end() || it2->second);
}

bool EventManager::IsMouseButtonHeld(Uint8 button) const
{
	auto it = mouseButtonState.find(button);
	return it != mouseButtonState.end() && it->second;
}

bool EventManager::GetMouseMoved() const
{
	return mouseMoved;
}

float EventManager::GetMouseScrollHorizontal() const
{
	return mouseScrollHorizontal;
}

float EventManager::GetMouseScrollVertical() const
{
	return mouseScrollVertical;
}

void EventManager::GetMousePosition(float& mouseX, float& mouseY) const
{
	mouseX = this->mouseX;
	mouseY = this->mouseY;
}

//- - - - - - - -

void EventManager::Getimgfo(bool open)
{
	isImGuiWindowHovered = open;
}

bool EventManager::IsImGuiWindowHovered() const
{
	return isImGuiWindowHovered;
}

Uint32 EventManager::GetOtherSDLEvent() const
{
	return OtherSDLEvents;
}