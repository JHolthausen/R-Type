#include "E_BigBullet.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


E_BigBullet::E_BigBullet(Surface* screen)
{
	this->screen = screen;
	image = new Surface("assets/ball.png");
	velocity = glm::vec2(-1.0, 0.0f);
}


E_BigBullet::~E_BigBullet()
{
}
