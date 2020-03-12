#include "CProjectile.h"

CProjectile::CProjectile(CVector2 startPosition, CVector2 velocity) :
	mPosition(startPosition),
	mVelocity(velocity),
	mRadius(2),
	mDamage(1)
{}


CProjectile::~CProjectile()
{}

void CProjectile::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
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

void CProjectile::Render(SDL_Renderer* Renderer) const
{
	SDL_RenderDrawLine(Renderer, mPosition.x, mPosition.y, mPosition.x, mPosition.y);
	SDL_RenderDrawLine(Renderer, mPosition.x - mRadius, mPosition.y, mPosition.x + mRadius, mPosition.y);
	SDL_RenderDrawLine(Renderer, mPosition.x, mPosition.y - mRadius, mPosition.x, mPosition.y + mRadius);
	SDL_RenderDrawLine(Renderer, mPosition.x - mRadius, mPosition.y - mRadius, mPosition.x + mRadius, mPosition.y + mRadius);
	SDL_RenderDrawLine(Renderer, mPosition.x + mRadius, mPosition.y - mRadius, mPosition.x - mRadius, mPosition.y + mRadius);
}

void CProjectile::Collision(/*CControlledObject& targetObject*/)
{
	//targetObject.Damage(mDamage);
}