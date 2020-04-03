#include "CPlayer.h"

CPlayer::CPlayer(CVector2 startPosition, std::vector<CProjectile>& PlayerBullets, SDL_Renderer* renderer, std::string textureName) :
	CControlledObject(startPosition, PlayerBullets, 5, renderer, textureName)
{}

CPlayer::~CPlayer()
{

}

void CPlayer::Update(float timeStep, EControlStyle& myControlStyle)
{
	CControlledObject::Update(timeStep);
	SetVelocity(GetVelocity() * dragMultiplier);

	const Uint8* keyInput = SDL_GetKeyboardState(NULL);

	//manages Player input
	switch (myControlStyle)
	{
	case(EControlStyle::Keyboard):
		if (keyInput[SDL_SCANCODE_W])
		{
			AddVelocity(CVector2(0, -moveSpeed));
		}
		if (keyInput[SDL_SCANCODE_S])
		{
			AddVelocity(CVector2(0, moveSpeed));
		}
		if (keyInput[SDL_SCANCODE_A])
		{
			AddVelocity(CVector2(-moveSpeed, 0));
		}
		if (keyInput[SDL_SCANCODE_D])
		{
			AddVelocity(CVector2(moveSpeed, 0));
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
		SetPosition(CVector2(mouseX, mouseY));
		break;

	}

	//keeps Player in bounds(window)
	if (mPosition.x < 0)
	{
		mPosition.x = 0;
		SetVelocity(CVector2(0, mVelocity.y));
	}
	if (mPosition.x > windowWidth)
	{
		mPosition.x = windowWidth;
		SetVelocity(CVector2(0, mVelocity.y));
	}
	if (mPosition.y < 0)
	{
		mPosition.y = 0;
		SetVelocity(CVector2(mVelocity.x, 0));
	}
	if (mPosition.y > windowHeight)
	{
		mPosition.y = windowHeight;
		SetVelocity(CVector2(mVelocity.x, 0));
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

void CPlayer::Render(SDL_Renderer& renderer) const
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mTextureRect);

	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i].Render(renderer);
	}
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