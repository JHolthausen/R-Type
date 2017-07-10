#pragma once

#include "EnemyParent.h"

namespace Tmpl8{
	class EnemyCircle : public EnemyParent
	{
	public:
		EnemyCircle(Surface* screen, double q);
		EnemyCircle(){};
		~EnemyCircle();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);
		virtual RECT GetAgroRect();
		BulletParent* Shoot(glm::vec2 target);

		float t = PI / 180; // pi is declared in template
		double q = 1;
		int r = 250;
		glm::vec2 pivot;
		Surface* img = new Surface("assets/ball.png");

	};

}