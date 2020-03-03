#include "Cvector2.h"

CVector2::CVector2(float xVal, float yVal) :
	x(xVal),
	y(yVal)
{}

CVector2::CVector2(Uint32 mousePoition) :
	x(mousePoition),
	y(mousePoition)
{}

CVector2::CVector2(CVector2 target, CVector2 origin) :
	x(target.x - origin.x),
	y(target.y - origin.y)
{}

CVector2::~CVector2()
{

}