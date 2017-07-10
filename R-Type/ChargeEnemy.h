#pragma once

#include "EnemyParent.h"


namespace Tmpl8{
	class ChargeEnemy : public EnemyParent
	{
	public:
		ChargeEnemy(Surface* screen, std::vector<std::vector<int>> ScreenMap);
		~ChargeEnemy();

		void Update(glm::vec2 target);
		void Draw(float x, float y, glm::vec2 camPos);
		BulletParent* Shoot(glm::vec2 target){ return NULL; };

		std::vector<std::vector<int>> ScreenMap;
	};

}