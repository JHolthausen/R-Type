#include "BigBullet.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


BigBullet::BigBullet(Surface* screen)
{

	this->screen = screen;
	image = new Surface("assets/bigbullet.png");
	velocity = glm::vec2(2.0, 0.0f);
	isBigBullet = true;
}


BigBullet::~BigBullet()
{
}
