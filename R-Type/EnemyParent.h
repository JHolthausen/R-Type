#pragma once

#include "template.h"
#include "surface.h"
#include <vector>
#include "BulletParent.h"
#include "E_SmallBullet.h"

namespace Tmpl8{
	class EnemyParent
	{
	public:
		EnemyParent();
		~EnemyParent();

		virtual void Draw(float x, float y, glm::vec2 camPos);
		virtual void Update(glm::vec2 target);
		virtual RECT GetAgroRect();
		virtual BulletParent* Shoot(glm::vec2 target);
		virtual void CheckCollision(){};
		virtual void UpdateDrawTimers(){};
		virtual void Shot(){};
		virtual void HandleDead(){};
		virtual RECT GetRect();


		Surface* screen;
		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
		
		std::vector<BulletParent*> bullets;
		Surface* image;

		glm::vec2 speed = glm::vec2(1.0f, 1.0f);

		bool isCircle = false;
		bool isKill = false;
		bool hasPowerUp = false;
		bool isBom = false;
		bool isBoss = false;
		bool isDestroy = false;

		int maxShootCounter = 100;
		int shootCounter = 0;

		int points = 10;

		glm::vec2 target = glm::vec2(0.0f, 0.0f);

		int hp = 1;
		int xSprites = 0;
	};

}