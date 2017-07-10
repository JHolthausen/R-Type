#include "BosTail.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

BosTail::BosTail(Surface* screen)
{
	this->screen = screen;

	image = new Surface("assets/ball.png");

}


BosTail::~BosTail()
{
}


void BosTail::Update(glm::vec2 t)
{
	if (this->target != glm::vec2(0.0f, 0.0f))
	{
		position.y = target.y + ((position.y - target.y)/2);
	}
}