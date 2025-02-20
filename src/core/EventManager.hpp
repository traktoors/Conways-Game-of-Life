#pragma once

#include <SDL3/SDL_events.h>
#include <unordered_map>

class EventManager
{
private:
	EventManager() {}
	~EventManager() = default;

	bool shouldQuit = false;

	std::unordered_map<SDL_Scancode, bool> keyState;
	std::unordered_map<SDL_Scancode, bool> keyStatePrev;

	std::unordered_map<Uint8, bool> mouseButtonState;
	std::unordered_map<Uint8, bool> mouseButtonStatePrev;
	float mouseScrollVertical = 0, mouseScrollHorizontal = 0;
	bool mouseMoved = false;
	float mouseX = 0, mouseY = 0;

	bool isImGuiWindowHovered = false;

	SDL_Scancode lastKeyPressed = SDL_SCANCODE_UNKNOWN;

	Uint32 OtherSDLEvents = 0;

public:
	static EventManager& GetInstance();

	// Prevent Copying
	EventManager(const EventManager&) = delete;
	EventManager& operator = (const EventManager&) = delete;

	void Getimgfo(bool hovered); // Sends to EventManager if any imgui window is hovered
	void PollEvents();
	bool ShouldQuit() const;

	bool IsKeyPressed(SDL_Scancode key) const;
	bool IsKeyReleased(SDL_Scancode key) const;
	bool IsKeyHeld(SDL_Scancode key) const;

	bool IsMouseButtonPressed(Uint8 button) const;
	bool IsMouseButtonReleased(Uint8 button) const;
	bool IsMouseButtonHeld(Uint8 button) const;
	bool GetMouseMoved() const;
	float GetMouseScrollVertical() const;
	float GetMouseScrollHorizontal() const;
	void GetMousePosition(float& mouseX, float& mouseY) const;
	SDL_Scancode GetLastKeyPressed() const;

	bool IsImGuiWindowHovered() const;

	Uint32 GetOtherSDLEvent() const;	// SDL Events that EventManager doesnt check
};