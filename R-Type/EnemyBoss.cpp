#include "EnemyBoss.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyBoss::EnemyBoss(Surface* screen)
{
	this->screen = screen;

	image = new Surface("assets/bos.png");
	shootCounter = 0;
	maxShootCounter = 100;
	isBoss = true;
}


EnemyBoss::~EnemyBoss()
{
}

int jk = 0; 
BulletParent* EnemyBoss::Shoot(glm::vec2 target)
{
	shootCounter++;
	jk++;
	if (!(GetAgroRect().left >= target.x || GetAgroRect().right <= target.x ||
		GetAgroRect().top >= target.y || GetAgroRect().bottom <= target.y))
	{
		if (shootCounter > maxShootCounter + 20)
		{
			shootCounter = 0;
		}
		if (shootCounter > maxShootCounter && jk  > 3)
		{
			jk = 0;
			BulletParent* tmp = new E_BigBullet(screen);

			glm::vec2 t;
			t.y = target.y - (position.y + image->GetHeight() / 2);
			t.x = target.x - (position.x + image->GetWidth() / 2);

			int d = std::sqrt(pow(t.x, 2) + pow(t.y, 2));


			//normalize vector
			tmp->velocity.y = t.y / d;
			tmp->velocity.x = t.x / d;

			tmp->position.x = position.x + image->GetWidth()/2;
			tmp->position.y = position.y + image->GetHeight()/2;
			return tmp;
		}





	}
	return NULL;


}


RECT EnemyBoss::GetAgroRect()
{
	int a = 10000;

	RECT tmp;
	tmp.left = position.x - a;
	tmp.top = position.y - a;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;
}