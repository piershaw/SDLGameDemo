#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	
}


SDL_Rect GameObject::spawn() {
	SDL_Rect playerShape;
	char move = '0';
	playerShape.x = 0;
	playerShape.y = 0;
	playerShape.w = 32;
	playerShape.h = 32;
	playerShape.x = W / 2;
	playerShape.y = H / 2;
	playerShape.w = 32;
	playerShape.h = 32;
	float gravity = 0.0f;
	float fVx = 0.0f;
	float fVy = 0.0f;
	float xV = 0.0f;
	float yV = 0.0f;
	int x = W / 2;
	int y = H / 2;

	return playerShape;
}

GameObject::~GameObject()
{
}
