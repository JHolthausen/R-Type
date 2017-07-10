#include "EnemyCircleBom.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyCircleBom::EnemyCircleBom(Surface* screen, double q)
{
	this->screen = screen;
	this->q = q;
	image = new Surface("assets/ball.png");
	pivot = glm::vec2(7950.0f, 300.0f);
	q = 1;
	r = 250;
	isBom = true;
	isCircle = true;
}


EnemyCircleBom::~EnemyCircleBom()
{
}


void EnemyCircleBom::Draw(float x, float y, glm::vec2 camPos)
{

	image->CopyTo(screen, x, y);

}

void EnemyCircleBom::Update(glm::vec2 target)
{
	position = glm::vec2(pivot.x + this->r * std::cos(q * t), pivot.y + this->r * std::sin(q*t));
	q++;
}

