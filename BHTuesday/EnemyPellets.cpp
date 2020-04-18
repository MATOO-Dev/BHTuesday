#include "EnemyPellets.h"

EnemyPellets::EnemyPellets(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer) :
	CEnemy(targetPosition, velocity, target, EnemyBullets, renderer, "EnemyPellets.png", EEnemyType::Pellets)
{}

void EnemyPellets::Update(float timeStep)
{
	//std::cout << mPosition.y << std::endl;

	mPosition = (mPosition + (mVelocity * timeStep));
	mTextureRect.x = (int)mPosition.x - mTextureRect.w / 2;
	mTextureRect.y = (int)mPosition.y - mTextureRect.h / 2;

	switch (mEnemyState)
	{
	case EEnemyState::Intro:
		if (mPosition.y >= mTargetPosition.y)
		{
			mVelocity.y = 0;
			mEnemyState = EEnemyState::Idle;
		}
		break;
	case EEnemyState::Idle:
		mEnemyState = EEnemyState::Shoot;
		break;
	case EEnemyState::Shoot:
		Shoot();
		mVelocity = mIntroVelocity * -1;
		mEnemyState = EEnemyState::Outro;
		break;
	case EEnemyState::Outro:
		if (OutOfBounds())
			Damage(mHealth);
		break;
	default:
		break;
	}
}

void EnemyPellets::Render()
{
	if (mTexture != nullptr)
	{
		if (mEnemyState != EEnemyState::Outro)
			SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);
		else
			SDL_RenderCopyEx(mRenderer, mTexture, NULL, &mTextureRect, 180, NULL, SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderDrawLine(mRenderer, (int)mPosition.x - 10, (int)mPosition.y - 10, (int)mPosition.x + 10, (int)mPosition.y + 10);
		SDL_RenderDrawLine(mRenderer, (int)mPosition.x + 10, (int)mPosition.y - 10, (int)mPosition.x - 10, (int)mPosition.y + 10);
	}
}

void EnemyPellets::Shoot()
{
	mBullets->push_back(CProjectile(CVector2(mPosition.x + 34, mPosition.y + 20), CVector2(targetPlayer->GetPosition(), mPosition).Normalize() * 500, 5));
	mBullets->push_back(CProjectile(CVector2(mPosition.x - 34, mPosition.y + 20), CVector2(targetPlayer->GetPosition(), mPosition).Normalize() * 500, 5));
}