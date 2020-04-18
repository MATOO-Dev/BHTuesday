#include "CProjectile.h"

CProjectile::CProjectile(CVector2 startPosition, CVector2 velocity, int radius) :
	mPosition(startPosition),
	mVelocity(velocity),
	mRadius(radius),
	mDamage(1)
{}


CProjectile::~CProjectile()
{}

bool CProjectile::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
	if (inBounds() == false)
		return false;
	return true;
}

bool CProjectile::inBounds() const
{
	if (GetPosition().x < 0 || GetPosition().x > windowWidth)
	{
		return false;
	}
	if (GetPosition().y < 0 || GetPosition().y > windowHeight)
	{
		return false;
	}
	return true;
}

void CProjectile::Render(SDL_Renderer& Renderer) const
{
	SDL_RenderDrawLine(&Renderer, (int)mPosition.x, (int)mPosition.y, (int)mPosition.x, (int)mPosition.y);
	SDL_RenderDrawLine(&Renderer, (int)mPosition.x - mRadius, (int)mPosition.y, (int)mPosition.x + mRadius, (int)mPosition.y);
	SDL_RenderDrawLine(&Renderer, (int)mPosition.x, (int)mPosition.y - mRadius, (int)mPosition.x, (int)mPosition.y + mRadius);
	SDL_RenderDrawLine(&Renderer, (int)mPosition.x - mRadius, (int)mPosition.y - mRadius, (int)mPosition.x + mRadius, (int)mPosition.y + mRadius);
	SDL_RenderDrawLine(&Renderer, (int)mPosition.x + mRadius, (int)mPosition.y - mRadius, (int)mPosition.x - mRadius, (int)mPosition.y + mRadius);
}

bool CProjectile::PlayerCollision(CPlayer& target)
{
	if (mPosition.GetDistance(target.GetPosition()) < (mRadius + target.GetRadius() - 10))
	{
		target.Damage((float)mDamage);
		return true;
	}
	return false;
}

bool CProjectile::EnemyCollision(CEnemy& target)
{
	if (mPosition.GetDistance(target.GetPosition()) < (mRadius + target.GetRadius() - 10))
	{
		target.Damage((float)mDamage);
		return true;
	}
	return false;
}