#pragma once

#include "CEnemy.h"
class EnemyPellets : public CEnemy
{
public:
	EnemyPellets(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer);
	void Update(float timeStep) override;
	void Render() override;
	void Shoot() override;
};

