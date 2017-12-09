// for windows
//#ifdef _WIN32 // well just for vs
#include "stdafx.h"
//#endif
 
#include "SDL.h"
#include "SDL_main.h"
#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_pixels.h" 
#include "SDL_rect.h"
#include "stdio.h"
#include "stdlib.h"

/* Define window size */
#define W 480
#define H 640
#define main SDL_main // ahh so SDL needs main(int argc, char *argv[]) main it cant be empty or SDLmain.dll will not be called
void makeWindow();

int main(int argc, char *argv[]){
	printf("hello world");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	makeWindow();

	return 0;
}




void makeWindow() {
	printf("Tank Made");

SDL_Window *mainWindow = SDL_CreateWindow("GAME", 100, 100, W, H, SDL_WINDOW_SHOWN);
SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, 0);//SDL_RENDERER_ACCELERATED
SDL_Event *mainevent = new SDL_Event();

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

	int wallsoffset = 10;
	bool gameRunning = true;

	while (gameRunning && mainevent->type != SDL_QUIT)
	{
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		//SDL_Delay(10);
		SDL_PollEvent(mainevent);
		SDL_RenderClear(render);


		SDL_SetRenderDrawColor(render, 200, 0, 0, 255);
		SDL_RenderDrawRect(render, &playerShape);
		SDL_RenderDrawLine(render, (int)playerShape.x + playerShape.w / 2, (int)playerShape.y + playerShape.h / 2, (int)playerShape.x + playerShape.w + 10, (int)playerShape.y + playerShape.h / 2);

		//Walls


		SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
		SDL_RenderDrawLine(render, wallsoffset, wallsoffset, W - wallsoffset, wallsoffset);//top
		SDL_RenderDrawLine(render, wallsoffset, wallsoffset, wallsoffset, H - wallsoffset);//left
		SDL_RenderDrawLine(render, W - wallsoffset, wallsoffset, W - wallsoffset, H - wallsoffset);//right
		SDL_RenderDrawLine(render, wallsoffset, H - wallsoffset, W - wallsoffset, H - wallsoffset);//bottom

		SDL_RenderPresent(render);

	}


	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(render);
	delete mainevent;

	SDL_Quit();
}