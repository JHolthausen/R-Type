#include "PowerUp.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff



PowerUp::PowerUp(Surface* screen)
{
	this->screen = screen;
}


PowerUp::~PowerUp()
{
}


void PowerUp::Draw(float x, float y)
{
	image->CopyTo(screen, x, y);
}

void PowerUp::Update()
{
	/*position += velocity;

	if (position.x < 0 ||
		position.x > PLYSCRNWIDTH)
	{
		outOfScreen = true;
	}*/



}

RECT PowerUp::GetRect()
{

	RECT tmp;
	tmp.left = position.x;
	tmp.top = position.y;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;


}
