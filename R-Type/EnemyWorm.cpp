#include "EnemyWorm.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyWorm::EnemyWorm(Surface* screen, glm::vec2 pivot, int q)
{
	this->screen = screen;
	image = new Surface("assets/enemycharge.png");

	velocity = glm::vec2(-5.0f, 0.0f);
	this->pivot = pivot;
	this->q = q;
	
}


EnemyWorm::~EnemyWorm()
{
}

void EnemyWorm::Draw(float x, float y, glm::vec2 camPos)
{
	image->CopyTo(screen, x, y);
}

void EnemyWorm::Update(glm::vec2 target)
{
	if (pivot.y > 10){
		switch (i)
		{
		case 1:
			position = glm::vec2(pivot.x + this->r * std::cos(q * t), pivot.y + this->r * std::sin(q*t));
			q--;
			if (q == -90)
				i = 2;
			break;
		case 2:
			break;

		}
	}
	else
	{
		switch (i)
		{
		case 1:
			position = glm::vec2(pivot.x + this->r * std::cos(q * t), pivot.y + this->r * std::sin(q*t));
			q++;
			if (q == 800)
				i = 2;
			break;
		case 2:
			break;

		}
	}

	EnemyParent::Update(target);
}