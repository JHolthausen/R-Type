#pragma once

#include "template.h"
#include "surface.h"
#include "game.h"

#include "BulletParent.h"
#include <vector>
#include "Tile.h"
#include "EnemyParent.h"
#include "Gun.h"
#include "BigBullet.h"
#include "SmallBullet.h"



namespace Tmpl8{
	class Player
	{
	public:
		Player(Surface* screen);
		~Player();
		
		void Draw(float x, float y);
		void Update(std::vector<std::vector<int>> ScreenMap, std::vector<EnemyParent*> Enemys, RECT cameraRect, std::vector<BulletParent*> bullets);
		void HandleInput();
		void Move(RECT camerRect);
		void CheckCollision(std::vector<std::vector<int>> ScreenMap, std::vector<EnemyParent*> Enemys, std::vector<BulletParent*> bullets);
		RECT GetRect();
		void HandleBullets(RECT cameraRect, std::vector<std::vector<int>> ScreenMap);
		void Shoot(int i);
		void HandleGun(RECT cameraRect);

		Surface* screen;

		//animation
		int imgState = 0;
		Surface* img_Default = new Surface("assets/player.png");
		Surface* img_Up = new Surface("assets/pink.png");
		Surface* img_Down = new Surface("assets/grey.png");
		Surface* img_Destroy = new Surface("assets/boom.png");


		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		glm::vec2 p_Speed = glm::vec2(10.0f, 10.0f);



		//for death animation
		int deathCntr = 0;
		int maxDeathCntr = 20;

		//player stats
		int lives = 3;
		int score = 0;
		bool isKill = false;
		bool canShoot = true;

		std::vector<BulletParent*> bullets;
		Gun* gun;
		int timerCount = 0;
		int beamCount = 0;
		bool hasGun = false;
		bool frontGun = false;
		bool createGun = true;
		int state = 1;
	};

}




