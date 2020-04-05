#pragma once

#include "CEnemy.h"
#include <math.h>

class EnemyKamikaze : public CEnemy
{
public:
	EnemyKamikaze(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer);
	~EnemyKamikaze();
	void Update(float timeStep) override;
	void Render() override;
};

