#include "CEnemy.h"

CEnemy::CEnemy(CVector2 startPosition, CPlayer* target, std::vector<CProjectile>& EnemyBullets) :
	CControlledObject(startPosition, EnemyBullets, 5),
	targetPlayer(target)
{}

CEnemy::~CEnemy()
{}

void CEnemy::Update(float timeStep)
{
	CControlledObject::Update(timeStep);

	Shoot();
}

void CEnemy::Render(SDL_Renderer& renderer) const
{
	SDL_RenderDrawLine(&renderer, mPosition.x - 10, mPosition.y - 10, mPosition.x + 10, mPosition.y + 10);
	SDL_RenderDrawLine(&renderer, mPosition.x + 10, mPosition.y - 10, mPosition.x - 10, mPosition.y + 10);
}

void CEnemy::Shoot()
{
	mBullets.push_back(CProjectile(mPosition, CVector2(targetPlayer->GetPosition(), mPosition).normalize() * 500));
}

void CEnemy::Damage(float damage)
{
	mHealth -= damage;
	if (mHealth < 0)
		Kill();
}

void CEnemy::Kill()
{
	std::cout << "enemy is kill" << std::endl;
}