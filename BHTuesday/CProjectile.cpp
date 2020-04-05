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
	SDL_RenderDrawLine(&Renderer, mPosition.x, mPosition.y, mPosition.x, mPosition.y);
	SDL_RenderDrawLine(&Renderer, mPosition.x - mRadius, mPosition.y, mPosition.x + mRadius, mPosition.y);
	SDL_RenderDrawLine(&Renderer, mPosition.x, mPosition.y - mRadius, mPosition.x, mPosition.y + mRadius);
	SDL_RenderDrawLine(&Renderer, mPosition.x - mRadius, mPosition.y - mRadius, mPosition.x + mRadius, mPosition.y + mRadius);
	SDL_RenderDrawLine(&Renderer, mPosition.x + mRadius, mPosition.y - mRadius, mPosition.x - mRadius, mPosition.y + mRadius);
}

bool CProjectile::PlayerCollision(CPlayer& target)
{
	if (mPosition.GetDistance(target.GetPosition()) < (mRadius + target.GetRadius() - 10))
	{
		target.Damage(mDamage);
		return true;
	}
	return false;
}

bool CProjectile::EnemyCollision(CEnemy& target)
{
	if (mPosition.GetDistance(target.GetPosition()) < (mRadius + target.GetRadius() - 10))
	{
		target.Damage(mDamage);
		return true;
	}
	return false;
}