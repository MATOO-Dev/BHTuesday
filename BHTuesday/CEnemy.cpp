#include "CEnemy.h"

CEnemy::CEnemy(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer, std::string textureName, EEnemyType type) :
	targetPlayer(target),
	mTargetPosition(targetPosition),
	mPosition(CVector2(targetPosition.x, -100)),
	mVelocity(velocity),
	mIntroVelocity(velocity),
	mHealth(5),
	mBullets(EnemyBullets),
	mRenderer(renderer),
	mTexture(CAssetManager::LoadTexture(mRenderer, textureName)),
	mTextureRect(CAssetManager::CreateTextureRect(mTexture, 1.5)),
	mRadius(mTextureRect.w / 2),
	mEnemyType(type),
	mEnemyState(EEnemyState::Intro)
{}

CEnemy::~CEnemy()
{
	delete targetPlayer;
	delete[] mBullets;
	delete mRenderer;
	SDL_DestroyTexture(mTexture);
	delete mTexture;
}

void CEnemy::Update(float timeStep)
{
	if (mPosition.y >= mTargetPosition.y)
		mVelocity.y = 0;
	//same for vel.x for diagonally moving enemys?

	mPosition = (mPosition + (mVelocity * timeStep));
	mTextureRect.x = int(mPosition.x - mTextureRect.w / 2);
	mTextureRect.y = int(mPosition.y - mTextureRect.h / 2);

	Shoot();
}

void CEnemy::Render()
{
	if (mTexture != nullptr)
		SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);
	else
	{
		SDL_RenderDrawLine(mRenderer, (int)mPosition.x - 10, (int)mPosition.y - 10, (int)mPosition.x + 10, (int)mPosition.y + 10);
		SDL_RenderDrawLine(mRenderer, (int)mPosition.x + 10, (int)mPosition.y - 10, (int)mPosition.x - 10, (int)mPosition.y + 10);
	}
}

void CEnemy::Shoot()
{
	//change position based on target
	mBullets->push_back(CProjectile(mPosition, CVector2(targetPlayer->GetPosition(), mPosition).Normalize() * 500, 2));
}

void CEnemy::Damage(float damage)
{
	mHealth -= damage;
}

bool CEnemy::OutOfBounds()
{
	//if this is below window, return true, if this is left/right of window, and also in the lower half, return true
	return(((mPosition.x < 0 || mPosition.x > windowWidth) && mPosition.y > windowHeight / 2) || mPosition.y > windowHeight);
	//prevents enemys being in the lower half of the window while not being visible, used to prevent 'surprise attacks'
}

bool CEnemy::IntersectsPlayer()
{
	if (mPosition.GetDistance(targetPlayer->GetPosition()) < (mRadius + targetPlayer->GetRadius()))
	{
		targetPlayer->Damage(1);
		return true;
	}
	return false;
}