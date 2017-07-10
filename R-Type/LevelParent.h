#pragma once


#include "template.h"
#include "surface.h"
#include "Tile.h"
#include <vector>
#include "EnemyParent.h"
#include "BulletParent.h"
#include "Player.h"
#include "PowerUp.h"

using std::vector;

namespace Tmpl8 {
	class LevelParent
	{
		

	public:
		
		LevelParent();
		~LevelParent();

		void InitScreenMap(int width, int height);
		virtual void Update(Player* p, RECT camera);
		virtual	void InitEnemys(){};
		vector<vector<int> > ScreenMap;
		vector<EnemyParent*> enemys;
		vector<BulletParent*> bullets;
		std::vector<PowerUp*> powers;
		vector<EnemyParent*> bosTail;

		Surface* image;
		Surface* screen;

		int scrnMapWidth, scrnMapHeight;
		bool bosDead = false;

		
	};

}