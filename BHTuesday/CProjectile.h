#pragma once

class CControlledObject;

#include "CVector2.h"
#include "Defines.h"
#include "CControlledObject.h"
#include <iostream>
#include <SDL.h>

class CProjectile
{
public:
	CProjectile(CVector2 startPosition, CVector2 velocity);
	~CProjectile();
	void Update(float timeStep);
	bool inBounds() const;
	void Render(SDL_Renderer* Renderer) const;
	void SetPosition(CVector2 newPosition);
	CVector2 GetPosition() const;
	void SetVelocity(CVector2 newVelocity);
	CVector2 GetVelocity() const;
	void Collision(/*CControlledObject& targetObject*/);
private:
	CVector2 mPosition;
	CVector2 mVelocity;
	int mDamage;
	int mRadius;
};

inline void CProjectile::SetPosition(CVector2 newPosition)
{
	mPosition = newPosition;
}

inline CVector2 CProjectile::GetPosition() const
{
	return mPosition;
}

inline void CProjectile::SetVelocity(CVector2 newVelocity)
{
	mVelocity = newVelocity;
}

inline CVector2 CProjectile::GetVelocity() const
{
	return mVelocity;
}