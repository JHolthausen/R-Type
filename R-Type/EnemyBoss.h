#pragma once

#include "EnemyParent.h"
#include "E_BigBullet.h"

namespace Tmpl8{
	class EnemyBoss : public EnemyParent
	{
	public:
		EnemyBoss(Surface* screen);
		~EnemyBoss();

		BulletParent* Shoot(glm::vec2 target);
		RECT GetAgroRect();
	};

}