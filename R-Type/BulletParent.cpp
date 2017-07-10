#include "BulletParent.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


BulletParent::BulletParent()
{
}


BulletParent::~BulletParent()
{
}


RECT BulletParent::GetRect()
{

	RECT tmp;
	tmp.left = position.x;
	tmp.top = position.y;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;


}

void BulletParent::Draw(float x, float y)
{
	image->CopyTo(screen, x, y);
}

void BulletParent::Update()
{
	glm::vec2 t = position + velocity * speed;
	if (t.x <= 0 || t.y <= 0 ||
		t.x >= 14200)
	{
		isKill = true;
	}
	else { position += velocity * speed; }
}