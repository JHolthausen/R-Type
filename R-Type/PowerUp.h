#pragma once

#include "template.h"
#include "surface.h"
#include "game.h"

namespace Tmpl8{
	class PowerUp
	{
	public:
		PowerUp(Surface* screen);
		~PowerUp();

		void Update();
		void Draw(float x, float y);
		RECT GetRect();

		Surface* image = new Surface("assets/power.png");
		Surface* screen;

		glm::vec2 position, velocity;

		bool outOfScreen = false;

	};

}