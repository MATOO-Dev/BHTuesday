#include "CEnemy.h"

CEnemy::CEnemy(CVector2 startPosition, CPlayer* target) :
	CControlledObject(startPosition),
	targetPlayer(target)
{}

CEnemy::~CEnemy()
{}

void CEnemy::Update(float timeStep)
{
	CControlledObject::Update(timeStep);

	Shoot();

	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i].Update(timeStep);
		if (mBullets[i].inBounds() == false)
		{
			mBullets.erase(mBullets.begin() + i);
		}
	}
}

void CEnemy::Render(SDL_Renderer& renderer) const
{
	SDL_RenderDrawLine(&renderer, mPosition.x - 10, mPosition.y - 10, mPosition.x + 10, mPosition.y + 10);
	SDL_RenderDrawLine(&renderer, mPosition.x + 10, mPosition.y - 10, mPosition.x - 10, mPosition.y + 10);

	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i].Render(&renderer);
	}
}

void CEnemy::Shoot()
{
	mBullets.push_back(CBullet(mPosition, CVector2(targetPlayer->GetPosition(), mPosition).normalize() * 500));
}

void CEnemy::Damage(float damage)
{
	mHealth -= damage;
}

void CEnemy::Kill()
{
	std::cout << "enemy is kill";
}