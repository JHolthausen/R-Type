#include "SmallBullet.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


SmallBullet::SmallBullet(Surface* screen)
{
	this->screen = screen;
	image = new Surface("assets/bullet.png");
	velocity = glm::vec2(3.0, 0.0f);
}


SmallBullet::~SmallBullet()
{
}
