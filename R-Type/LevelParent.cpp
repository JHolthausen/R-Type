#include "LevelParent.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff




LevelParent::LevelParent()
{
}

LevelParent::~LevelParent()
{
}


void LevelParent::InitScreenMap(int width, int height)
{
	//the grid size is image size devided by tilesize
	int u = height / TILESIZE;
	int j = width / TILESIZE;

	scrnMapWidth = j;
	scrnMapHeight = u;

	//set the size of the 2d vector array
	ScreenMap.resize(u);

	for (int i = 0; i < u; ++i)
	{
		ScreenMap[i].resize(j);
	}
}

void LevelParent::Update(Player* p, RECT camera)
{

	//get the enmeybullets
	for each(EnemyParent* enemy in enemys)
	{

		enemy->Update(p->position);
		BulletParent* b = enemy->Shoot(p->position);
		if (b != NULL)
		{
			bullets.push_back(b);
		}
	}


	for (int j = 0; j < bullets.size(); j++)
	{
		//delete bullets out of screen
		if (camera.left >= bullets[j]->GetRect().right || camera.right <= bullets[j]->GetRect().left ||
			camera.top >= bullets[j]->GetRect().bottom || camera.bottom <= bullets[j]->GetRect().top)
		{
			delete bullets[j];
			bullets.erase(bullets.begin() + j);

		}
	}

	for (int j = 0; j < bullets.size(); j++)
	{
		//delete bullets hit walls
		int a = bullets[j]->position.x / TILESIZE;
		int b = bullets[j]->position.y / TILESIZE;

		//0 is nothing
		if (ScreenMap[b][a] != 0 || bullets[j]->isKill)
		{
			delete bullets[j];
			bullets.erase(bullets.begin() + j);

		}


	}

	for (int j = 0; j < bullets.size(); j++)
	{
		bullets[j]->Update();
	}

/*
//	check collision
//	player bullet hit enemy*/

	//out level
	for (int i = 0; i < enemys.size(); i++)
	{
		if (enemys[i]->position.x < 0 || enemys[i]->isKill)
		{
			if (enemys[i]->isBoss)
			{
					bosDead = true;
					p->score += enemys[i]->points;
			}
			
				delete enemys[i];
				enemys.erase(enemys.begin() + i);
			
		}
	}


	for (int i = 0; i < enemys.size(); i++)
	{
		for (int j = 0; j < p->bullets.size(); j++)
		{
			if (!(enemys[i]->GetRect().left >= p->bullets[j]->GetRect().right || enemys[i]->GetRect().right <= p->bullets[j]->GetRect().left ||
				enemys[i]->GetRect().top >= p->bullets[j]->GetRect().bottom || enemys[i]->GetRect().bottom <= p->bullets[j]->GetRect().top))
			{
				if (!p->bullets[j]->isBigBullet || (p->bullets[j]->isBigBullet && enemys[i]->isCircle))
				{
					delete p->bullets[j];
					p->bullets.erase(p->bullets.begin() + j);
				}
				//kil the cickele
				if (enemys[i]->isBom)
				{
					for each(EnemyParent* e in enemys)
					{
						if (e->isCircle)
						{
							e->isDestroy = true ;
						}
					}
					enemys[i]->isBom = false;
				}
				else if (!enemys[i]->isCircle)
				{
					//enemy has powerup
					if (enemys[i]->hasPowerUp)
					{
						PowerUp* pow = new PowerUp(screen);
						pow->position = enemys[i]->position;
						powers.push_back(pow);
					}
					if (enemys[i]->isBoss)
					{
						enemys[i]->hp--;
					}
					else{
						p->score += enemys[i]->points;
						delete enemys[i];
						enemys.erase(enemys.begin() + i);
					}
				}
				break;
			}
		}
	}

	//check if player hit power up
	for (int i = 0; i < powers.size(); i++)
	{
		if (!(powers[i]->GetRect().left >= p->GetRect().right || powers[i]->GetRect().right <= p->GetRect().left ||
			powers[i]->GetRect().top >= p->GetRect().bottom || powers[i]->GetRect().bottom <= p->GetRect().top))
		{
			p->state++;
			delete powers[i];
			powers.erase(powers.begin() + i);
		}
	}

}