#pragma once

#include "EnemyParent.h"

namespace Tmpl8{
	class BosTail : public EnemyParent
	{
	public:
		BosTail(Surface* screen);
		~BosTail();


		//glm::vec2 target = glm::vec2(0.0f, 0.0f);
		void Update(glm::vec2 target);
		BulletParent* Shoot(glm::vec2 target){ return NULL; };
	};

}