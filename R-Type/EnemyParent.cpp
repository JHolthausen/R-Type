#include "EnemyParent.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


EnemyParent::EnemyParent()
{
}


EnemyParent::~EnemyParent()
{
}

RECT EnemyParent::GetRect()
{

	RECT tmp;
	tmp.left = position.x;
	tmp.top = position.y;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;


}

void EnemyParent::Update(glm::vec2 target)
{
	position += velocity*speed;
}

RECT EnemyParent::GetAgroRect()
{
	int a = 400;

	RECT tmp;
	tmp.left = position.x -a;
	tmp.top = position.y -a;
	tmp.right = position.x + image->GetWidth() + a;
	tmp.bottom = position.y + image->GetHeight() + a;

	return tmp;



}


BulletParent* EnemyParent::Shoot(glm::vec2 target)
{
	shootCounter++;
	
	if (position.y > 0 && position.x > 0)
	{
		if (!(GetAgroRect().left >= target.x || GetAgroRect().right <= target.x ||
			GetAgroRect().top >= target.y || GetAgroRect().bottom <= target.y))
		{
			if (shootCounter > maxShootCounter && rand() % 3 > 1)
			{
				shootCounter = 0;
				BulletParent* tmp = new E_SmallBullet(screen);

				glm::vec2 t;
				t.y = target.y - position.y;
				t.x = target.x - position.x;

				int d = std::sqrt(pow(t.x, 2) + pow(t.y, 2));


				//normalize vector
				tmp->velocity.y = t.y / d;
				tmp->velocity.x = t.x / d;

				tmp->position = position;
				return tmp;
			}




		}
	}
		return NULL;

	
}

void EnemyParent::Draw(float x, float y, glm::vec2 camPos)
{
	image->CopyTo(screen, x, y);
}