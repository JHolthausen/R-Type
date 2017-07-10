#pragma once

#include "EnemyParent.h"
#include "template.h"
#include "surface.h"
#include "BulletParent.h"
#include "E_Boss_Bullet.h"
#include <vector>
#include "Tile.h"
#include "E_Boss_Tail_Piece.h"
#include "E_Boss_Explosion.h"

namespace Tmpl8 {
	class E_Boss : public EnemyParent
	{
	public:
		E_Boss(Surface* screen);
		~E_Boss();

		void Draw(float x, float y, glm::vec2 CameraPos);
		void Update(glm::vec2 target);
		void UpdateTimers();
		//void Shot();
		void InitTiles();
		void HandleTail();
		int GrabTile(int Rows, int Cols, Surface* img);
		void InitTail();
		void HandleDead();
		BulletParent* Shoot(glm::vec2 target);
		RECT GetAgroRect();

		Surface* bossImage = new Surface("assets/boss/bossSheet.png");
		Surface* bossDrawImage = new Surface(170,214);
		int maxBossState = 2;
		int bossState = maxBossState;
		int bossTimer = 0;
		int maxBossTimer = 20;
		int bossStateMplyr = 1;
		
		Surface* monsterImage = new Surface("assets/boss/monsterSheet.png");
		Surface* monsterDrawImage = new Surface(monsterImage->GetWidth() / 9, monsterImage->GetHeight());
		int maxMonsterState = 8;
		int monsterState = maxMonsterState;
		int monsterTimer = 0;
		int maxMonsterTimer = 20;
		int monsterStateMplyr = 1;

		int jk = 0;

		//explosions
		std::vector<E_Boss_Explosion*> explosions;


		int maxShotBullets = 4; // the bullets the bos shoots

		std::vector<std::vector<int>> imageMap;
		std::vector<Tile*> Tiles;
		int TileCounter = 0;
		int SimpleCnt = 0;

		//vars for tail 
		std::vector<E_Boss_Tail_Piece*> tail;
		float t = PI / 180; // pi is declared in template
		double q = 202;
		int r = 250;
		glm::vec2 pivot;
		int cntr = 1;
		int tailTimer = 0;
		int maxTailTimer = 5;

		bool inScreen = false; // bool to start update when enemy is drawn
		bool isDying = false; // start dead animation
		bool exploding = false; // bool to init explosions

		glm::vec2 screenPos;

	};

}