#pragma once

#include "EnemyParent.h"

namespace Tmpl8{
	class EnemyCircleBom : public EnemyParent
	{
	public:
		EnemyCircleBom(Surface* screen, double q);
		EnemyCircleBom(){};
		~EnemyCircleBom();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);

		BulletParent* Shoot(glm::vec2 target){ return NULL; };

		float t = PI / 180; // pi is declared in template
		double q = 1;
		int r = 250;
		glm::vec2 pivot;


	};

}