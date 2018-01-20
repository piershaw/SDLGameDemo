#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#include"Shader.h"
#include "Object3D.h"


// Our object has 4 points

const uint32_t points = 4;



// Each poin has three values ( x, y, z)

const uint32_t floatsPerPoint = 3;



// Each color has 4 values ( red, green, blue, alpha )

const uint32_t floatsPerColor = 4;



// This is the object we'll draw ( a simple square

const GLfloat diamond[points][floatsPerPoint] = {

	{ -0.5,  0.5,  0.5 }, // Top left

	{ 0.5,  0.5,  0.5 }, // Top right

	{ 0.5, -0.5,  0.5 }, // Bottom right 

	{ -0.5, -0.5,  0.5 }, // Bottom left

};



// This is the object we'll draw ( a simple square

const GLfloat colors[points][floatsPerColor] = {

	{ 0.0, 1.0, 0.0, 1.0 }, // Top left

	{ 1.0, 1.0, 0.0, 1.0 }, // Top right

	{ 1.0, 0.0, 0.0, 1.0 }, // Bottom right 

	{ 0.0, 0.0, 1.0, 1.0 }, // Bottom left

};



// Create variables for storing the ID of our VAO and VBO

GLuint vbo[2], vao[1];



// The positons of the position and color data within the VAO

const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;



// Our wrapper to simplify the shader code
#define GL3_PROTOTYPES 1
#define PROGRAM_NAME "VertextShader"
Shader shader;

Object3D::Object3D(SDL_Window * mainWindow)
{
	window = mainWindow;
	SDL_GL_SwapWindow(window);
}


Object3D::~Object3D()
{
}

bool Object3D::setupBufferObjects(){

	// Generate and assign two Vertex Buffer Objects to our handle
	glewExperimental = GL_TRUE;
	glewInit();

	glGenBuffers(2, vbo); // somthings wrong here



	// Generate and assign a Vertex Array Object to our handle

	glGenVertexArrays(1, vao);



	// Bind our Vertex Array Object as the current used object

	glBindVertexArray(vao[0]);



	// Positions

	// ===================

	// Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);



	// Copy the vertex data from diamond to our buffer

	glBufferData(GL_ARRAY_BUFFER, (points * floatsPerPoint) * sizeof(GLfloat), diamond, GL_STATIC_DRAW);



	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);



	// Enable our attribute within the current VAO

	glEnableVertexAttribArray(positionAttributeIndex);



	// Colors

	// =======================

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);



	// Copy the vertex data from diamond to our buffer

	glBufferData(GL_ARRAY_BUFFER, (points * floatsPerColor) * sizeof(GLfloat), colors, GL_STATIC_DRAW);



	// Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

	glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);



	// Note : We didn't enable the colors here!



	// Set up shader ( will be covered in the next part )

	// ===================

	if (!shader.Init())
		return false;

	shader.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	return true;

}


void Object3D::render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// drawLines
	// Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
	//glDrawArrays(GL_LINE_LOOP, 0, 4); // drawLines
	
	// Enable our attribute within the current VAO
	glEnableVertexAttribArray(colorAttributeIndex);

	// Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// Swap our buffers to make our changes visible
	SDL_GL_SwapWindow(window);
}
