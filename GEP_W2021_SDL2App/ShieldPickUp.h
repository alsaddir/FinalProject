#pragma once
#include "SpriteEx.h"

class ShieldPickUp : public SpriteEx
{
private:
	float rotationSpeed;

public:
	ShieldPickUp(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed)
		:SpriteEx(text, srcRect, destRect), rotationSpeed(rotSpeed)
	{
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius = 100;

	}

	void Update()
	{
		angle += rotationSpeed;
	}

};

