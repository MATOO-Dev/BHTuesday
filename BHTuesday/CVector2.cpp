#include "Cvector2.h"

CVector2::CVector2(float xVal, float yVal) :
	x(xVal),
	y(yVal)
{}

CVector2::CVector2(Uint32 mousePoition) :
	x((float)mousePoition),
	y((float)mousePoition)
{}

CVector2::CVector2(CVector2 target, CVector2 origin) :
	x(target.x - origin.x),
	y(target.y - origin.y)
{}

float CVector2::GetDistance(const CVector2 other) const
{
	CVector2 connection = CVector2(other - *this);
	return connection.length();
}