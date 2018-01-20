#pragma once
#include "SDL_rect.h"
#include "Constants.h"

class GameObject
{

public:
	SDL_Rect playerShape;
	char move;
	float gravity;
	float fVx;
	float fVy;
	float xV;
	float yV;
	int x;
	int y;

	GameObject();
	~GameObject();

	SDL_Rect spawn();
};

