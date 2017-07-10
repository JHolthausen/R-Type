#include "Level1.h"
#include "E_Boss.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff


Level1::Level1(Surface* screen)
{
	this->screen = screen;
	image = new Surface("assets/stage1.png");

	//set the grid size
	LevelParent::InitScreenMap(image->GetWidth(), image->GetHeight());
}

Level1::~Level1()
{
}

void Level1::InitEnemys()
{
	EnemyParent* tmp;
	
	//---------------------------------
	//create fighters
	//----

	for (int i = 0; i < 4; i++)
	{
		tmp = new EnemyFighter(screen);
		tmp->position = glm::vec2(2000.0f + 100 * i, 400.0f);
		enemys.push_back(tmp);
	}

	enemys.back()->hasPowerUp = true;

	for (int i = 0; i < 4; i++)
	{
		tmp = new EnemyFighter(screen);
		tmp->position = glm::vec2(4000.0f + 100 * i, 400.0f);
		enemys.push_back(tmp);
	}
	enemys.back()->hasPowerUp = true;

	for (int i = 0; i < 4; i++)
	{
		tmp = new EnemyFighter(screen);
		tmp->position = glm::vec2(45000.0f + 100 * i, 200.0f);
		enemys.push_back(tmp);
	}

	enemys.back()->hasPowerUp = true;

	//---------------------------------
	//create circle formation
	//----
	for (int i = 0; i < 27; i++)
	{
		if (i == 4)
		{
			tmp = new EnemyCircleBom(screen, 12 * i);
			enemys.push_back(tmp);
		}
		else
		{
			tmp = new EnemyCircle(screen, 12 * i);
			enemys.push_back(tmp);
		}
	}

	//---------------------------------
	//create Turrets formation
	//----
	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(8700.0f, 450.0f);
	enemys.push_back(tmp);


	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(8850.0f, 450.0f);
	enemys.push_back(tmp);

	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(9750.0f, 450.0f);
	enemys.push_back(tmp);


	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(9870.0f, 450.0f);
	enemys.push_back(tmp);

	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(1300.0f, 450.0f);
	enemys.push_back(tmp);

	tmp = new EnemyTurret(screen);
	tmp->position = glm::vec2(3300.0f, 450.0f);
	enemys.push_back(tmp);

	//---------------------------------
	//create groundBots formation
	//----
	tmp = new EnemyGroundBot(screen, ScreenMap);
	tmp->position = glm::vec2(750.0f, 500.0f);
	enemys.push_back(tmp);

	tmp = new EnemyGroundBot(screen, ScreenMap);
	tmp->position = glm::vec2(3500.0f, 500.0f);
	enemys.push_back(tmp);

	tmp = new EnemyGroundBot(screen, ScreenMap);
	tmp->position = glm::vec2(4300.0f, 500.0f);
	enemys.push_back(tmp);

	tmp = new EnemyGroundBot(screen, ScreenMap);
	tmp->position = glm::vec2(2300.0f, 500.0f);
	enemys.push_back(tmp);

	//---------------------------------
	//create charge Enemys 
	//----
	tmp = new ChargeEnemy(screen , ScreenMap);
	tmp->position = glm::vec2(5900,400.0f);
	enemys.push_back(tmp);

	tmp = new ChargeEnemy(screen, ScreenMap);
	tmp->position = glm::vec2(5800, 200.0f);
	enemys.push_back(tmp);

	tmp = new ChargeEnemy(screen, ScreenMap);
	tmp->position = glm::vec2(6400, 250.0f);
	enemys.push_back(tmp);

	tmp = new ChargeEnemy(screen, ScreenMap);
	tmp->position = glm::vec2(6000, 420.0f);
	enemys.push_back(tmp);

	tmp = new ChargeEnemy(screen, ScreenMap);
	tmp->position = glm::vec2(6100, 150.0f);
	enemys.push_back(tmp);

	//---------------------------------
	//create jump Enemys 
	//----
	tmp = new JumpEnemy(screen);
	tmp->position = glm::vec2(11850, 375.0f);
	enemys.push_back(tmp);


	enemys.back()->hasPowerUp = true;

	//---------------------------------
	//create boss Enemys 
	//----
	tmp = new E_Boss(screen);
	tmp->position = glm::vec2(13120.0f, 64);
	enemys.push_back(tmp);

	//---------------------------------
	//create boss tail 
	//----
	//for (int i = 0; i < 12; i++)
	//{
	//	
	//	BosTail* b = new BosTail(screen);
	//	if (i > 0)
	//	{
	//		b->target = bosTail.back()->position;
	//	}
	//	tmp = b;
	//	tmp->position = glm::vec2(12800.0f + tmp->image->GetWidth()* i, 500);
	//	bosTail.push_back(tmp);
	//}
}

void Level1::Update(Player* p, RECT camera)
{
	LevelParent::Update(p, camera);

	if (wrmSpawnCount >= maxWrmSpawnCount)
	{
		CreateWorm();
		wrmSpawnCount = 0;
	}

	wrmSpawnCount++;
}

void Level1::CreateWorm()
{
	EnemyParent* tmp;
	int r = rand() % 3 + 1;

	for (int i = 0; i < 4; i++)
	{
		int q = 0;
		glm::vec2 pivot;

		switch (r)
		{
		case 1:

			q = 629 - i * 10;
			pivot = glm::vec2(7100.0f, 0.0f);
			tmp = new EnemyWorm(screen, pivot, q);
			enemys.push_back(tmp);

			break;
		case 2:
			q = 629 - i * 10;
			pivot = glm::vec2(9400.0f, 0.0f);
			tmp = new EnemyWorm(screen, pivot, q);
			enemys.push_back(tmp);

			break;
		case 3:
			q = i * 10;
			pivot = glm::vec2(5100.0f, 640.0f);
			tmp = new EnemyWorm(screen, pivot, q);
			enemys.push_back(tmp);

			break;
		}



	}

	enemys.back()->hasPowerUp = true;


}