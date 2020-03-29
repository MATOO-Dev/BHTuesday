#pragma once
#include <SDL.h>

class CVector2
{
public:
	CVector2(float xVal, float yVal);
	CVector2(Uint32 mousePosition);
	CVector2(CVector2 target, CVector2 origin);
	float length();
	CVector2 normalize();
	float GetDistance(const CVector2 other) const;
	~CVector2();
	float x;
	float y;
};

inline CVector2 operator+ (const CVector2& first, const CVector2& second)
{
	return CVector2(first.x + second.x, first.y + second.y);
}

inline CVector2 operator- (const CVector2 first, const CVector2 second)
{
	return CVector2(first.x - second.x, first.y - second.y);
}

inline CVector2 operator*(const CVector2& base, const float& multiplier)
{
	return(CVector2(base.x * multiplier, base.y * multiplier));
}

inline float CVector2::length()
{
	return(sqrt((x * x) + (y * y)));
}

inline CVector2 CVector2::normalize()
{
	return(CVector2(x / this->length(), y / this->length()));
}