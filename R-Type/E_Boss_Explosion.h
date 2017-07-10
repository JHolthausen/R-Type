#pragma once
#include "template.h"
#include "surface.h"

namespace Tmpl8 {
	class E_Boss_Explosion
	{

	public:
		E_Boss_Explosion(Surface* screen, Surface* Image, int maxTimer, int sprites, glm::vec2 Position);
		~E_Boss_Explosion();

		bool Update();
		bool UpdateTimers();
		void Draw();

		Surface* screen;
		Surface* image;
		Surface* drawImage;

		int timer = 0;
		int maxTimer;
		int sprites;
		int state = 0; // update before draw
		int width = 0;
		int height = 0;

		glm::vec2 Position;

	};

}