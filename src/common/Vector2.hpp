#pragma once
#include <type_traits>
#include <functional>

template <typename T>
struct Vector2	// Supports only int or float
{
	static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>, "Vector2 only supports int or float");

	T x, y;

	Vector2() : x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}

	Vector2& operator += (const Vector2<T>& other)
	{
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	Vector2& operator *= (const Vector2<T>& other)
	{
		this->x *= other.x;
		this->y *= other.y;

		return *this;
	}

	bool operator == (const Vector2<T>& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	struct Hash
	{
		size_t operator()(const Vector2<T>& v) const
		{
			return std::hash<T>{}(v.x) ^ (std::hash<T>{}(v.y) << 1);
		}
	};
};