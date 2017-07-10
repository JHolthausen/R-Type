#pragma once

#include "EnemyParent.h"

namespace Tmpl8{
	class EnemyWorm : public EnemyParent
	{
	public:
		EnemyWorm(Surface* screen, glm::vec2 pivot, int q);
		~EnemyWorm();

		void Update(glm::vec2 target);
		void Draw(float x, float y, glm::vec2 camPos);

		std::vector<glm::vec2> trackVelocity; //preset velocity
		int count = 0;
		int i = 1;


		float t = PI / 180; // pi is declared in template
		double q = 1;
		int r = 250;
		glm::vec2 pivot;
	};

}