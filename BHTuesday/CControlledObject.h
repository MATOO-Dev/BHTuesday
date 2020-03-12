#pragma once
#include "CVector2.h"
#include "CBullet.h"
#include <vector>


class CControlledObject
{
public:
	CControlledObject(CVector2 startPosition);
	~CControlledObject();
	virtual void Update(float timeStep);
	virtual void Render(SDL_Renderer& renderer) const = 0;
	const CVector2& GetPosition() const;
	void SetPosition(CVector2 newPosition);
	const CVector2& GetVelocity() const;
	void SetVelocity(CVector2 newVelocity);
	void AddVelocity(CVector2 addend);
	virtual void Shoot() = 0;
	virtual void Damage(float damage) = 0;
	virtual void Kill() = 0;
protected:
	CVector2 mPosition;
	CVector2 mVelocity;
	float mHealth;
	std::vector<CBullet> mBullets;
};


inline const CVector2& CControlledObject::GetPosition() const
{
	return mPosition;
}

inline void CControlledObject::SetPosition(CVector2 newPosition)
{
	mPosition = newPosition;
}

inline const CVector2& CControlledObject::GetVelocity() const
{
	return mVelocity;
}

inline void CControlledObject::SetVelocity(CVector2 newVelocity)
{
	mVelocity = newVelocity;
}

inline void CControlledObject::AddVelocity(CVector2 addend)
{
	mVelocity = mVelocity + addend;
}