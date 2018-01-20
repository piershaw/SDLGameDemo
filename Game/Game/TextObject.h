#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class TextObject
{
public:
	TextObject();
	~TextObject();
	void drawText(string message, vector<int, int>* position);
};


