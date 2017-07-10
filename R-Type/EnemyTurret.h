#pragma once

#include "EnemyParent.h"


namespace Tmpl8{
	class EnemyTurret : public EnemyParent
	{
	public:
		EnemyTurret(Surface* screen);
		~EnemyTurret();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);

	};

}