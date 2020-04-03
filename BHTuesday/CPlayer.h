#pragma once

class CProjectile;

#include "Cvector2.h"
#include "Defines.h"
#include "CProjectile.h"
#include "CAssetManager.h"
#include <vector>
#include <SDL_image.h>
#include <iostream>
#include <SDL.h>


class CPlayer
{
public:
	CPlayer(CVector2 startPosition, std::vector<CProjectile>& PlayerBullets, SDL_Renderer* renderer, std::string textureName);
	~CPlayer();
	void Update(float timeStep, EControlStyle& myControlStyle);
	void Render();
	void Shoot();
	void Damage(float damage);
	void Kill();
	CVector2 GetPosition();
	int GetRadius();
	float GetHealth();
private:
	std::vector<CProjectile>& mBullets;
	CVector2 mPosition;
	CVector2 mVelocity;
	const float moveSpeed = 50;
	const float dragMultiplier = 0.75;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Rect mTextureRect;
	float mHealth;
	int mRadius;
};

inline CVector2 CPlayer::GetPosition()
{
	return mPosition;
}

inline int CPlayer::GetRadius()
{
	return mRadius;
}

inline float CPlayer::GetHealth()
{
	return mHealth;
}