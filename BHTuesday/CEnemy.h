#pragma once

#include "CPlayer.h"
#include "CProjectile.h"
#include "CAssetManager.h"
#include <vector>
#include <SDL_image.h>

class CEnemy
{
public:
	CEnemy(CVector2 startPosition, CPlayer* target, std::vector<CProjectile>& EnemyBullets, SDL_Renderer* renderer, std::string textureName);
	~CEnemy();
	void Update(float timeStep);
	void Render(SDL_Renderer& renderer) const;
	void Shoot();
	void Damage(float damage);
	void Kill();
private:
	CVector2 mPosition;
	CVector2 mVelocity;
	CPlayer* targetPlayer;
	std::vector<CProjectile>& mBullets;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Rect mTextureRect;
	float mHealth;
	int mRadius;
};