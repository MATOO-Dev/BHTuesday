#pragma once
#include "CControlledObject.h"
#include "CPlayer.h"

class CEnemy : public CControlledObject
{
public:
	CEnemy(CVector2 startPosition, CPlayer* target, std::vector<CProjectile>& EnemyBullets);
	~CEnemy();
	void Update(float timeStep) override;
	void Render(SDL_Renderer& renderer) const;
	void Shoot() override;
	void Damage(float damage) override;
	void Kill()override;
private:
	CPlayer* targetPlayer;
};

