#include "JumpEnemy.h"
#include "E_BigBullet.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


JumpEnemy::JumpEnemy(Surface* screen)
{
	this->screen = screen;

	image = new Surface("assets/alien.png");
	velocity = glm::vec2(0.0f, -1.0f);
	speed = glm::vec2(0.0f, 3.0f);

	maxShootCounter = 40;
}
JumpEnemy::~JumpEnemy()
{}

void JumpEnemy::Draw(float x, float y, glm::vec2 camPos)
{
	image->CopyTo(screen, x, y);
}

void JumpEnemy::Update(glm::vec2 target)
{
	if (count > maxcount)
	{
		velocity.y *= -1;
		count = 0;
	}
	EnemyParent::Update(target);

	count++;

}


BulletParent* JumpEnemy::Shoot(glm::vec2 target)
{
	shootCounter++;

	if (!(GetAgroRect().left >= target.x || GetAgroRect().right <= target.x ||
		GetAgroRect().top >= target.y || GetAgroRect().bottom <= target.y))
	{
		if (shootCounter > maxShootCounter)
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
			tmp->position = position;
			return tmp;
		}
		




	}
	return NULL;


}


RECT JumpEnemy::GetAgroRect()
{
	int a = 10000;

	RECT tmp;
	tmp.left = position.x - a;
	tmp.top = position.y - a;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;



}