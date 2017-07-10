#include "EnemyCircle.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyCircle::EnemyCircle(Surface* screen, double q)
{
	this->screen = screen;
	this->q = q;
	image = new Surface("assets/circleEnemy.png");
	pivot = glm::vec2(7950.0f, 300.0f);
	q = 1;
	r = 250;
	isCircle = true;
}


EnemyCircle::~EnemyCircle()
{
}


void EnemyCircle::Draw(float x, float y, glm::vec2 camPos)
{
	if (!isDestroy)
	{
		image->CopyTo(screen, x, y);
	}
	else
	{
		img->CopyTo(screen, x, y);
	}
}

void EnemyCircle::Update(glm::vec2 target)
{
	position = glm::vec2(pivot.x + this->r * std::cos(q * t), pivot.y + this->r * std::sin(q*t));
	q++;
}

RECT EnemyCircle::GetAgroRect()
{
	int a = r - 10;

	RECT tmp;
	tmp.left = pivot.x - a;
	tmp.top = pivot.y - a;
	tmp.right = pivot.x  + a;
	tmp.bottom = pivot.y  + a;

	return tmp;

}

BulletParent* EnemyCircle::Shoot(glm::vec2 target)
{
	if (!isDestroy)
	{
		return EnemyParent::Shoot(target);
	}
	return NULL;
}