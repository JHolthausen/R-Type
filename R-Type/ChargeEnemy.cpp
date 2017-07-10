#include "ChargeEnemy.h"
#include "Tile.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


ChargeEnemy::ChargeEnemy(Surface* screen, std::vector<std::vector<int>> ScreenMap)
{
	this->screen = screen;
	this->ScreenMap = ScreenMap;
	image = new Surface("assets/charge1.png");
}


ChargeEnemy::~ChargeEnemy()
{
}

void ChargeEnemy::Draw(float x, float y, glm::vec2 camPos)
{
	image->CopyTo(screen, x, y);
}

void ChargeEnemy::Update(glm::vec2 target)
{
	if (!(GetAgroRect().left >= target.x || GetAgroRect().right <= target.x ||
		GetAgroRect().top >= target.y || GetAgroRect().bottom <= target.y))
	{
		glm::vec2 t;
		t.y = target.y - position.y;
		t.x = target.x - position.x;

		int d = std::sqrt(pow(t.x, 2) + pow(t.y, 2));


		//normalize vector
		velocity.y = t.y / d;
		velocity.x = t.x / d;
	}
	else
	{
		velocity = glm::vec2(0.0f, 0.0f);
	}

	/*int a = (position.y + velocity.y) / TILESIZE;
	int b = (position.x + velocity.x) / TILESIZE;

	if (ScreenMap[a][b] != 0)
	{
	}*/

	EnemyParent::Update(target);
}


