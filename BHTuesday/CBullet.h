#pragma once

class CControlledObject;

#include "CVector2.h"
#include "Defines.h"
#include "CControlledObject.h"
#include <iostream>
#include <SDL.h>

class CBullet
{
public:
	CBullet(CVector2 startPosition, CVector2 velocity);
	~CBullet();
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
	int mDiameter;
};

inline void CBullet::SetPosition(CVector2 newPosition)
{
	mPosition = newPosition;
}

inline CVector2 CBullet::GetPosition() const
{
	return mPosition;
}

inline void CBullet::SetVelocity(CVector2 newVelocity)
{
	mVelocity = newVelocity;
}

inline CVector2 CBullet::GetVelocity() const
{
	return mVelocity;
}