#include "CEnemy.h"

CEnemy::CEnemy(CVector2 startPosition, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer, std::string textureName) :
	targetPlayer(target),
	mPosition(startPosition),
	mVelocity(0, 0),
	mHealth(5),
	mBullets(EnemyBullets),
	mRenderer(renderer),
	mTexture(CAssetManager::LoadTexture(mRenderer, textureName)),
	mTextureRect(CAssetManager::CreateTextureRect(mTexture, 1.5)),
	mRadius(mTextureRect.w / 2)
{}

CEnemy::~CEnemy()
{
	delete targetPlayer;
	delete[] mBullets;
	delete mRenderer;
	delete mTexture;
}

void CEnemy::Update(float timeStep)
{
	mPosition = (mPosition + (mVelocity * timeStep));
	mTextureRect.x = mPosition.x - mTextureRect.w / 2;
	mTextureRect.y = mPosition.y - mTextureRect.h / 2;

	Shoot();
}

void CEnemy::Render()
{
	SDL_RenderDrawLine(mRenderer, mPosition.x - 10, mPosition.y - 10, mPosition.x + 10, mPosition.y + 10);
	SDL_RenderDrawLine(mRenderer, mPosition.x + 10, mPosition.y - 10, mPosition.x - 10, mPosition.y + 10);

	SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);
}

void CEnemy::Shoot()
{
	mBullets->push_back(CProjectile(mPosition, CVector2(targetPlayer->GetPosition(), mPosition).normalize() * 500));
}

void CEnemy::Damage(float damage)
{
	mHealth -= damage;
}