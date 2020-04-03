#include "CControlledObject.h"

CControlledObject::CControlledObject(CVector2 startPosition, std::vector<CProjectile>& EnemyBullets, int radius, SDL_Renderer* renderer, std::string textureName) :
	mPosition(startPosition),
	mVelocity(0, 0),
	mHealth(1),
	mBullets(EnemyBullets),
	mRenderer(renderer),
	mTexture(CAssetManager::LoadTexture(mRenderer, textureName)),
	mTextureRect(CAssetManager::CreateTextureRect(mTexture, 1.5)),
	mRadius(mTextureRect.w / 2)
{}

CControlledObject::~CControlledObject()
{

}

void CControlledObject::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
	mTextureRect.x = mPosition.x - mTextureRect.w / 2;
	mTextureRect.y = mPosition.y - mTextureRect.h / 2;
}