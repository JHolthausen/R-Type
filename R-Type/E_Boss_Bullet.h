#pragma once

#include "BulletParent.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8 {
	class E_Boss_Bullet : public BulletParent
	{
	public:
		E_Boss_Bullet(Surface* screen);
		~E_Boss_Bullet();

		void Draw(float x, float y);
		void Update();
		void UpdateDrawTimers();

		Surface* bulletImage = new Surface("assets/boss/BossBulletSheet.png");
		Surface* bulletDrawImage = new Surface(23, 23);
		int maxBulletState = 3;
		int bulletState = maxBulletState;
		int bulletTimer = 0;
		int maxBulletTimer = 10;
		int bulletStateMplyr = 1;



	};

}