#include "EnemyTurret.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyTurret::EnemyTurret(Surface* screen)
{
	this->screen = screen;
	image = new Surface("assets/turret2.png");

}


EnemyTurret::~EnemyTurret()
{
}


void EnemyTurret::Draw(float x, float y, glm::vec2 camPos)
{


	image->CopyTo(screen, x, y);

}

void EnemyTurret::Update(glm::vec2 target)
{

	//EnemyParent::Update();
}
