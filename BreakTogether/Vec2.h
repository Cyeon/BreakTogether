#pragma once
#include<cassert>

struct Vec2Int
{
	int x;
	int y;
};

class Vec2
{
public:
	float x;
	float y;
public:
	Vec2();
	~Vec2();
	Vec2 operator-(const Vec2& vec2) const;
	POINT toPoint();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(long _x, long _y);
	Vec2(POINT _pt);
	float Length();
	Vec2& Normalize();

	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator *(Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator /(Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator *(int _i)
	{
		return Vec2(x * static_cast<float>(_i), y * static_cast<float>(_i));
	}

	void operator +=(Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
};
