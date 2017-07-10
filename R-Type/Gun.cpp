#include "Gun.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff



Gun::Gun(Surface* screen)
{
	this->screen = screen;

}


Gun::~Gun()
{
}


void Gun::Draw(float x, float y)
{
	image->CopyTo(screen, x, y);

	//auto i = bullets.begin();
	//while (i != bullets.end())
	//{
	//	if ((*i)->gridPos.x > PLAYSCREENWIDTH / TILESIZE)
	//	{
	//		//bullets.erase(i++);   alternatively, 
	//		i = bullets.erase(i);
	//	}
	//	else
	//	{
	//		//other_code_involving(*i);
	//		(*i)->Update();
	//		(*i)->Draw();
	//		++i;
	//	}
	//}

}

BulletParent* Gun::Shoot(int i)
{
	BulletParent* tmp;
	switch (state)
	{
	case 1:
		if (i == 1){
			tmp = new SmallBullet(screen);
			tmp->position = position;
		}
		else if (i == 2)
		{
			/*tmp = new BigBullet(screen, tileFac);
			tmp->gridPos = gridPos;
			bullets.push_back(tmp);*/
		}
		break;
	case 2:
		//tmp = new SmallBullet(screen);
		//tmp->position = position;

		break;
	}

	return tmp;


}

void Gun::Update(RECT Camera)
{
	int tmp = position.x + velocity.x;

	if (!(tmp >= Camera.left + 800))
	{
		position += velocity;
	}
	else
	{
		position.x = Camera.left + 800;
	}

}


RECT Gun::GetRect()
{

	RECT tmp;
	tmp.left = position.x;
	tmp.top = position.y;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;


}
