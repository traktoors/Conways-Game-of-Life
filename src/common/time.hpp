#pragma once

class Time
{
private:
	Time() {}
	~Time() = default;

	double deltaTime = 0;
	Uint64 lastTicks = 0;
public:
	Time(const Time&) = delete;
	Time operator = (const Time&) = delete;

	static Time& GetInstance()
	{
		static Time time;
		return time;
	}


	double GetDelta()
	{
		return deltaTime;
	}

	void Update()
	{
		Uint64 nowTicks = SDL_GetTicks();
		deltaTime = double(nowTicks - lastTicks) / 1000.0f;
		lastTicks = nowTicks;
	}
};