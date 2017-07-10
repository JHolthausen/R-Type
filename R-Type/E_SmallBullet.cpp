#include "E_SmallBullet.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


E_SmallBullet::E_SmallBullet(Surface* screen)
{
	this->screen = screen;
	image = new Surface("assets/e_bullet.png");
	velocity = glm::vec2(-5.0, 0.0f);
}


E_SmallBullet::~E_SmallBullet()
{
}
