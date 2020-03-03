#pragma once

#include "Cvector2.h"
#include "CControlledObject.h"
#include "Defines.h"
#include <iostream>
#include <SDL.h>

class CPlayer : public CControlledObject
{
public:
	CPlayer(CVector2 startPosition);
	~CPlayer();
	void Update(float timeStep, EControlStyle& myControlStyle);
	void Render(SDL_Renderer& renderer) const override;
	void Shoot() override;
	void Damage(float damage) override;
private:
	const float moveSpeed = 50;
	const float dragMultiplier = 0.75;
};
