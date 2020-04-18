#pragma once
#include <SDL.h>

class CVector2
{
public:
	CVector2(float xVal, float yVal);
	CVector2(Uint32 mousePosition);
	CVector2(CVector2 target, CVector2 origin);
	float length();
	CVector2 Normalize();
	float GetDistance(const CVector2 other) const;
	static CVector2 Zero();
	float x;
	float y;
};

inline CVector2 operator+ (const CVector2 first, const CVector2 second)
{
	return CVector2(first.x + second.x, first.y + second.y);
}

inline CVector2 operator- (const CVector2 first, const CVector2 second)
{
	return CVector2(first.x - second.x, first.y - second.y);
}

inline CVector2 operator*(const CVector2 base, const float multiplier)
{
	return(CVector2(base.x * multiplier, base.y * multiplier));
}

inline bool operator==(const CVector2 first, const CVector2 second)
{
	return(first.x == second.x && first.y == second.y);
}

inline float CVector2::length()
{
	double tempX = double(x);
	double tempY = double(y);
	//used to circumvent C26451: Arithmetic overflow
	return((float)sqrt((tempX * tempX) + (tempY * tempY)));
}

inline CVector2 CVector2::Normalize()
{
	return(CVector2(x / this->length(), y / this->length()));
}

inline CVector2 CVector2::Zero()
{
	return(CVector2(0, 0));
}