#pragma once

#include "EnemyParent.h"


namespace Tmpl8{
	class EnemyFighter: public EnemyParent
	{
	public:
		EnemyFighter(Surface* screen);
		~EnemyFighter();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);

		glm::vec2 e_Speed = glm::vec2(1.0f, 1.0f);
		int count;
		int maxcount = 50;


	};

}