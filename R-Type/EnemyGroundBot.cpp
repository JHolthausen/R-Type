#include "EnemyGroundBot.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

EnemyGroundBot::EnemyGroundBot(Surface* screen, std::vector<std::vector<int>> ScreenMap)
{
	this->ScreenMap = ScreenMap;
	this->screen = screen;
	image = new Surface("assets/groundbot.png");
	velocity = glm::vec2(-3.0f, 0.0f);

	shootCounter = rand() % 300;
}


EnemyGroundBot::~EnemyGroundBot()
{
}


void EnemyGroundBot::Draw(float x, float y, glm::vec2 camPos)
{


	image->CopyTo(screen, x, y);

}

void EnemyGroundBot::Update(glm::vec2 target)
{
	CheckMove();
	EnemyParent::Update(target);
}

void EnemyGroundBot::CheckMove()
{

		glm::vec2 temp = position + velocity;
		int a = (temp.y + image->GetHeight())/ TILESIZE ;
		int b = temp.x / TILESIZE;
	
		if (ScreenMap[a][b] != 0)
		{
			velocity.x *= -1;
		}

		b = (temp.x + image->GetWidth()) / TILESIZE;
	
		if (ScreenMap[a][b] != 0)
		{
			velocity.x *= -1;
		}

}