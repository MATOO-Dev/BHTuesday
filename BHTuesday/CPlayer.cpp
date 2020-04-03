#include "CPlayer.h"

CPlayer::CPlayer(CVector2 startPosition, std::vector<CProjectile>& PlayerBullets, SDL_Renderer* renderer, std::string textureName) :
	mPosition(startPosition),
	mVelocity(0, 0),
	mHealth(3),
	mBullets(PlayerBullets),
	mRenderer(renderer),
	mTexture(CAssetManager::LoadTexture(mRenderer, textureName)),
	mTextureRect(CAssetManager::CreateTextureRect(mTexture, 1.5)),
	mRadius(mTextureRect.w / 2)
{}

CPlayer::~CPlayer()
{

}

void CPlayer::Update(float timeStep, EControlStyle& myControlStyle)
{
	mPosition = (mPosition + (mVelocity * timeStep));
	mTextureRect.x = mPosition.x - mTextureRect.w / 2;
	mTextureRect.y = mPosition.y - mTextureRect.h / 2;
	mVelocity = (mVelocity * dragMultiplier);

	const Uint8* keyInput = SDL_GetKeyboardState(NULL);

	//manages Player input
	switch (myControlStyle)
	{
	case(EControlStyle::Keyboard):
		if (keyInput[SDL_SCANCODE_W])
		{
			mVelocity = mVelocity + (CVector2(0, -moveSpeed));
		}
		if (keyInput[SDL_SCANCODE_S])
		{
			mVelocity = mVelocity + (CVector2(0, moveSpeed));
		}
		if (keyInput[SDL_SCANCODE_A])
		{
			mVelocity = mVelocity + (CVector2(-moveSpeed, 0));
		}
		if (keyInput[SDL_SCANCODE_D])
		{
			mVelocity = mVelocity + (CVector2(moveSpeed, 0));
		}
		if (keyInput[SDL_SCANCODE_SPACE])
		{
			Shoot();
		}
		break;

	case(EControlStyle::Mouse):
		int mouseX;
		int mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		mPosition = CVector2(mouseX, mouseY);
		break;

	}

	//keeps Player in bounds(window)
	if (mPosition.x < 0)
	{
		mPosition.x = 0;
		mVelocity = CVector2(0, mVelocity.y);
	}
	if (mPosition.x > windowWidth)
	{
		mPosition.x = windowWidth;
		mVelocity = CVector2(0, mVelocity.y);
	}
	if (mPosition.y < 0)
	{
		mPosition.y = 0;
		mVelocity = CVector2(mVelocity.x, 0);
	}
	if (mPosition.y > windowHeight)
	{
		mPosition.y = windowHeight;
		mVelocity = CVector2(mVelocity.x, 0);
	}
	/*
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i].Update(timeStep);
		for (int i = 0; i < enemys.size(); i++)
		{
			mBullets[i].Collision(enemys[i]);
		}
		if (mBullets[i].inBounds() == false)
		{
			mBullets.erase(mBullets.begin() + i);
		}
	}
	*/
}

void CPlayer::Render() 
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);
}

void CPlayer::Shoot()
{
	mBullets.push_back(CProjectile(mPosition, CVector2(0, -500)));
}

void CPlayer::Damage(float damage)
{
	mHealth -= damage;

	if (mHealth < 0)
	{
		Kill();
	}
}

void CPlayer::Kill()
{
	std::cout << "player is kill" << std::endl;
}