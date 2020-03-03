#include "CControlledObject.h"

CControlledObject::CControlledObject(CVector2 startPosition) :
	mPosition(startPosition),
	mVelocity(0, 0)
{}

CControlledObject::~CControlledObject()
{

}

void CControlledObject::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
}