#pragma once

#include "LevelParent.h"
#include <vector>
#include "EnemyFighter.h"
#include "EnemyCircle.h"
#include "EnemyWorm.h"
#include "EnemyTurret.h"
#include "EnemyGroundBot.h"
#include "ChargeEnemy.h"
#include "EnemyCircleBom.h"
#include "JumpEnemy.h"
#include "EnemyBoss.h"
#include "BosTail.h"

namespace Tmpl8 {

	class Level1 : public LevelParent
	{
	public:

		Level1(Surface* screen);
		~Level1();

		void InitEnemys();
		void Update(Player* p, RECT camera);
		void CreateWorm();


		int wrmSpawnCount = 0;
		int maxWrmSpawnCount = 300;

	};

}