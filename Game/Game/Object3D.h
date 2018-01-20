#pragma once
#include <GL\glew.h>
#include <stdint.h>
#include <SDL.h>

class Object3D
{
public:
	Object3D(SDL_Window * mainWindow);
	~Object3D();
	SDL_Window * window;
	bool setupBufferObjects();
	void render();
};

