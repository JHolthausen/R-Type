#include "EnemyFighter.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


EnemyFighter::EnemyFighter(Surface* screen)
{
	this->screen = screen;

	image = new Surface("assets/fighter.png");



	//little random generate
	int y = 0;
	int r = rand() % 2 + 1;

	if (r == 1)
	{
		y = 1;
	}
	else
	{
		y = -1;
	}
	velocity = glm::vec2(-1.0f, y);

	count = rand() % maxcount;

}


EnemyFighter::~EnemyFighter()
{
}

void EnemyFighter::Draw(float x, float y, glm::vec2 camPos)
{
	image->CopyTo(screen, x,y );
}

void EnemyFighter::Update(glm::vec2 target)
{
	if (count > maxcount)
	{
		velocity.y *= -1;
		count = 0;
	}
	position += velocity;

	count++;

}