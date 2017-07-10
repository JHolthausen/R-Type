#pragma once

#include "template.h"
#include "surface.h"
#include "BulletParent.h"
#include "SmallBullet.h"
#include "game.h"

namespace Tmpl8{

	class Gun
	{
	public:
		Gun(Surface* screen);
		~Gun();

		BulletParent* Shoot(int i);
		void Draw(float x, float y);
		void Update(RECT Camera);
		RECT GetRect();

		int state = 1;
		Surface* screen;


		glm::vec2 velocity = glm::vec2(5.0f, 0.0f);
		glm::vec2 position = glm::vec2(0.0f, CAMSCRHEIGHT / 2);


		//std::vector<BulletParent*> bullets;

		Surface* image = new Surface("assets/gun.png");

		int scrnMapWidth;
		int scrnMapHeight;

	};

}