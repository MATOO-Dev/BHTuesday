#include "CBullet.h"

CBullet::CBullet(CVector2 startPosition, CVector2 velocity) :
	mPosition(startPosition),
	mVelocity(velocity),
	mDiameter(4),
	mDamage(1)
{}


CBullet::~CBullet()
{}

void CBullet::Update(float timeStep)
{
	SetPosition(GetPosition() + (GetVelocity() * timeStep));
}

bool CBullet::inBounds() const
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

void CBullet::Render(SDL_Renderer* Renderer) const
{
	float radius = mDiameter / 2;
	SDL_RenderDrawLine(Renderer, mPosition.x, mPosition.y, mPosition.x, mPosition.y);
	SDL_RenderDrawLine(Renderer, mPosition.x - radius, mPosition.y, mPosition.x + radius, mPosition.y);
	SDL_RenderDrawLine(Renderer, mPosition.x, mPosition.y - radius, mPosition.x, mPosition.y + radius);
	SDL_RenderDrawLine(Renderer, mPosition.x - radius, mPosition.y - radius, mPosition.x + radius, mPosition.y + radius);
	SDL_RenderDrawLine(Renderer, mPosition.x + radius, mPosition.y - radius, mPosition.x - radius, mPosition.y + radius);
}

void CBullet::Collision(/*CControlledObject& targetObject*/)
{
	//targetObject.Damage(mDamage);
}