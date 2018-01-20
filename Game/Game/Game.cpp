
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


#include "Constants.h"
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_joystick.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <iostream>


#include <GL\glew.h>
#include "3rdPartyLibs\glm\glm\glm.hpp"
#include "3rdPartyLibs\glm\glm\gtx\transform.hpp"
#include <SDL_opengl.h>// might need

#include "GameObject.h"
#include "Object3D.h"

using namespace std;


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< notes I have to read this every time <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// I have to finish my text object and link the dll files in 3rdparty folder 
// try to get the windows to mix the open gl with sdl make the menu
// state all runing....


#define GL3_PROTOTYPES 1
#define main SDL_main // ahh so SDL needs main(int argc, char *argv[]) main it cant be empty or SDLmain.dll will not be called

//std::string programName = "Headerphile SDL2 - OpenGL thing";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window * mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;


void makeWindow();
bool setOpenGLAttributes();
void printSDL_GL_Attributes();
void checkSDLError(int line);
void runGame();
void cleanup();

//move this 


glm::mat4 model = glm::translate(glm::vec3(3, 1, 5));

glm::mat4 view = glm::lookAt
(
	glm::vec3(0, 0, -5), // Camera is at ( 0, 0, -5), in World Space
	glm::vec3(0, 0, 0), // And looks at the center
	glm::vec3(0, -1, 0)  // Camera is upside-down
);

glm::mat4 projection = glm::perspective
(
	45.0f,              // 45º field of view
	1920.0f / 1080.0f,  // 16:9 aspect ratio
	0.1f,               // Only render what's 0.1 or more away from camera
	100.0f              // Only render what's 100 or less away from camera
);

glm::mat4 modelViewProjection = projection * view * model;



int main(int argc, char *argv[]){
	printf("hello world");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	glewExperimental = GL_TRUE;
	glewInit();

	//openGL
	mainWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_OPENGL);
	// Create our opengl context and attach it to our window 
	mainContext = SDL_GL_CreateContext(mainWindow);
	setOpenGLAttributes();
	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);



	runGame();
	cleanup();
	//openGL

	//for Standerd SDL
	//makeWindow();
	//test

	return 0;
}

//opengl
bool setOpenGLAttributes()
{
	 	// Set our OpenGL version. 
		// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
		// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	 	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
		// Turn on double buffering with a 24bit Z buffer. 
		// You may need to change this to 16 or 32 for your system 
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
		 return true;
}


void makeWindow() {
	printf("Tank Made");


	mainWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_OPENGL);
	SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, 0);//SDL_RENDERER_ACCELERATED
	SDL_Event *mainevent = new SDL_Event();
	// Create our opengl context and attach it to our window 
	mainContext = SDL_GL_CreateContext(mainWindow);

	// This makes our buffer swap syncronized with the monitor's vertical refresh
	SDL_GL_SetSwapInterval(1);

	


	int wallsoffset = 10;
	bool gameRunning = true;

	while (gameRunning && mainevent->type != SDL_QUIT)
	{
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		//SDL_Delay(10);
		SDL_PollEvent(mainevent);
		SDL_RenderClear(render);
		GameObject * gameObject = new GameObject();
		SDL_Rect playerShape = gameObject->spawn();


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


	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);

	
	SDL_DestroyWindow(mainWindow);
	SDL_DestroyRenderer(render);
	delete mainevent;

	SDL_Quit();
}

void runGame()
{
	bool loop = true;
	Object3D * obj = new Object3D(mainWindow);
	//make object
	obj->setupBufferObjects();
	obj->render();


	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;
				case SDLK_r:
					// Cover with red and update
					glClear(GL_COLOR_BUFFER_BIT);
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(mainWindow);
					break;
				case SDLK_g:
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(mainWindow);
					break;
				case SDLK_b:
					// Cover with blue and update
					//glClearColor(0.0, 0.0, 1.0, 1.0);
					//glClear(GL_COLOR_BUFFER_BIT);


					obj->setupBufferObjects();
					obj->render();

					// make 3d
					cout << "Seting up VBO + VAO..." << endl;
					//if (!obj->setupBufferObjects()) { // I think its for shaders
						//cout << "not...working" << endl;
					//} else {
						cout << "Rendering..." << endl;
						//obj->render(mainWindow);
						cout << "Rendering done!\n" << endl;
					
					//}
					//cin.ignore();
					// make 3d

					//SDL_GL_SwapWindow(mainWindow);
					break;
				default:
					break;
				}
			}
		}

		// Swap our back buffer to the front
		// This is the same as :
		// 		SDL_RenderPresent(&renderer);
	}



	if (obj != nullptr)
		delete obj;
}

void cleanup()
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(mainContext);

	// Destroy our window
	SDL_DestroyWindow(mainWindow);

	// Shutdown SDL 2
	SDL_Quit();
}


void checkSDLError(int line = -1)
{

}

void printSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);

}
