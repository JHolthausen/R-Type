#include "E_boss_Bullet.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

E_Boss_Bullet::E_Boss_Bullet(Surface* screen)
{
	this->screen = screen;
	velocity = glm::vec2(2.0, 0.0f);
}


E_Boss_Bullet::~E_Boss_Bullet()
{
}

void E_Boss_Bullet::Draw(float x, float y)
{
	bulletImage->CopyTo(bulletDrawImage, 0 - 23 * bulletState, 0);

	//draw body;
	bulletDrawImage->CopyTo(screen, x, y);
}


void E_Boss_Bullet::Update()
{
	UpdateDrawTimers();
}

void E_Boss_Bullet::UpdateDrawTimers()
{
	//do next image for animation, if end reverse
	if (bulletTimer >= maxBulletTimer)
	{
		bulletTimer = 0;
		bulletState += bulletStateMplyr;

		if (bulletState < 0 || bulletState > maxBulletState)
		{
			bulletState = 0;;

		}
	}
	bulletTimer++;
}