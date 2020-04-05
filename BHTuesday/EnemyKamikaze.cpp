#include "EnemyKamikaze.h"

EnemyKamikaze::EnemyKamikaze(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer) :
	CEnemy(targetPosition, velocity, target, EnemyBullets, renderer, "EnemyKamikaze.png", EEnemyType::Kamikaze)
{}

EnemyKamikaze::~EnemyKamikaze()
{}

void EnemyKamikaze::Update(float timeStep)
{
	mPosition = (mPosition + (mVelocity * timeStep));
	mTextureRect.x = mPosition.x - mTextureRect.w / 2;
	mTextureRect.y = mPosition.y - mTextureRect.h / 2;

	if (OutOfBounds())
		mHealth = -1;

	switch (mEnemyState)
	{
	case EEnemyState::Intro:
		if (mPosition.y >= mTargetPosition.y)
			mVelocity = CVector2::Zero();
		////same for vel.x for diagonally moving enemys?
		if (mVelocity == CVector2::Zero())
			mEnemyState = EEnemyState::Idle;
		break;
	case EEnemyState::Idle:
		SDL_Delay(2);
		mTargetPosition = targetPlayer->GetPosition();
		mVelocity = CVector2(mPosition, mTargetPosition).Normalize() * -1;
		mVelocity = mVelocity * 500;
		mEnemyState = EEnemyState::Shoot;
		break;
	case EEnemyState::Shoot:
		break;
	case EEnemyState::Outro:
		//not applicable for this enemy type
		break;
	default:
		break;
	}
}

void EnemyKamikaze::Render()
{
	if (mTexture != nullptr)
	{
		if (mEnemyState != EEnemyState::Shoot)
			SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);
		else
		{
			//float angle = atan2(mTargetPosition.y, mTargetPosition.x) * 180 / 3.14159265;
			//if (mTargetPosition.x > mPosition.x)
			//	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &mTextureRect, -90 + angle, NULL, SDL_FLIP_NONE);
			//else
			//	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &mTextureRect, -55 + angle, NULL, SDL_FLIP_NONE);
			CVector2 delta = mPosition - mTargetPosition;
			float angle = atan2(delta.y, delta.x) * 180 / 3.14159265; 
			SDL_RenderCopyEx(mRenderer, mTexture, NULL, &mTextureRect, -55 + angle, NULL, SDL_FLIP_NONE);

		}
	}
	else
	{
		SDL_RenderDrawLine(mRenderer, mPosition.x - 10, mPosition.y - 10, mPosition.x + 10, mPosition.y + 10);
		SDL_RenderDrawLine(mRenderer, mPosition.x + 10, mPosition.y - 10, mPosition.x - 10, mPosition.y + 10);
	}
}