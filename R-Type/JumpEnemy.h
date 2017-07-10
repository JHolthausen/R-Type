#pragma once

#include "EnemyParent.h"


namespace Tmpl8{
	class JumpEnemy : public EnemyParent
	{
	public:
		JumpEnemy(Surface* screen);
		~JumpEnemy();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);
		BulletParent* Shoot(glm::vec2 target);
		RECT GetAgroRect();

		int count = 0;
		int maxcount = 50;


	};

}