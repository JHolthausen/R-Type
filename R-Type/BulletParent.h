#pragma once

#include "template.h"
#include "surface.h"
#include <vector>
#include "BulletParent.h"

namespace Tmpl8{
	class BulletParent
	{
	public:
		BulletParent();
		~BulletParent();

		void Draw(float x, float y);
		void Update();
		RECT GetRect();

		Surface* screen;
		glm::vec2 position, velocity , speed = glm::vec2(10.0f,10.f);
		std::vector<BulletParent*> bullets;
		Surface* image;

		bool isBigBullet = false;
		bool isKill = false;

	};

}