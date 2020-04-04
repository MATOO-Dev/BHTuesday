#pragma once

class CProjectile;

#include "CVector2.h"
#include "CPlayer.h"
#include "CProjectile.h"
#include "CAssetManager.h"
#include <vector>
#include <SDL_image.h>


class CEnemy
{
public:
	CEnemy(CVector2 targetPosition, CVector2 velocity, CPlayer* target, std::vector<CProjectile>* EnemyBullets, SDL_Renderer* renderer, std::string textureName);
	~CEnemy();
	virtual void Update(float timeStep);
	virtual void Render();
	virtual void Shoot();
	void Damage(float damage);
	CVector2 GetPosition();
	int GetRadius();
	float GetHealth();
private:
	CVector2 mPosition;
	CVector2 mTargetPosition;
	CVector2 mVelocity;
	CPlayer* targetPlayer;
	std::vector<CProjectile>* mBullets;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Rect mTextureRect;
	float mHealth;
	int mRadius;
};

inline CVector2 CEnemy::GetPosition()
{
	return mPosition;
}

inline int CEnemy::GetRadius()
{
	return mRadius;
}

inline float CEnemy::GetHealth()
{
	return mHealth;
}