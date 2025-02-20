#pragma once

namespace Math
{
	static void ClampF(float& value, float min, float max)
	{
		if (value > max)
			value = max;
		else if (value < min)
			value = min;
	}
}