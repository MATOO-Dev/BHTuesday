#include "CControlledObject.h"

CControlledObject::CControlledObject(CVector2 startPosition, std::vector<CProjectile>& EnemyBullets) :
	mPosition(startPosition),
	mVelocity(0, 0),
	mHealth(1),
	mBullets(EnemyBullets)
{}

CControlledObject::~CControlledObject()
{

}

void CControlledObject::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
}