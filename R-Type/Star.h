#pragma once

#include "template.h"
#include "surface.h"
#include "game.h"

namespace Tmpl8
{
	class Star
	{
	public:
		//default constructor/desstructor
		Star(Surface* screen);
		~Star();

		//custom function
		void Draw();

		//declare variables
		Surface* screen;
		glm::vec2 position;
		glm::vec2 velocity = glm::vec2(rand() % 5 - 6 , 0.0f);		//set random y velocity to get difrent star speed 
		Pixel color;
		int r;
	};
}