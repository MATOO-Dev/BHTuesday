#include "CControlledObject.h"

CControlledObject::CControlledObject(CVector2 startPosition, std::vector<CProjectile>& EnemyBullets, int radius, SDL_Renderer* renderer, std::string textureName) :
	mPosition(startPosition),
	mVelocity(0, 0),
	mHealth(1),
	mBullets(EnemyBullets),
	mRadius(radius),
	mRenderer(renderer),
	mTexture(CAssetManager::LoadTexture(mRenderer, textureName))
{}

CControlledObject::~CControlledObject()
{

}

void CControlledObject::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
}

void CControlledObject::SetTexture(std::string filename)
{
}