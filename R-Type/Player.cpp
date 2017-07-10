#include "Player.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Player::Player(Surface* screen)
{
	this->screen = screen;
}


Player::~Player()
{
}

void Player::Draw(float x, float y)
{

	img_Default->CopyTo(screen, x, y);

	//beam bar
	screen->Bar(600, 660, 600 + (20 * 10), 670, 0x99CCFF);
	screen->Bar(600, 660, 600 + (beamCount * 10), 670, 0x0000ff);

	screen->Print("Beam", 550, 660, 0xffffff);

	
}

void Player::Update(std::vector<std::vector<int>> ScreenMap, std::vector<EnemyParent*> enemys, RECT camerRect, std::vector<BulletParent*> bullets)
{
	//fail safe
	if (state > 4)
	{
		state = 4;
	}

	HandleInput();
	Move(camerRect);
	HandleBullets(camerRect, ScreenMap);
	//CheckCollision(ScreenMap ,  enemys, bullets); // disable this for easy walktrough

 	if (state > 1)
	{
		if (createGun)
		{
			gun = new Gun(screen);
			gun->position.x = camerRect.left;
			createGun = false;
		}

		HandleGun(camerRect);
	}


}

void Player::HandleInput()
{
	if (!isKill)
	{
		//left arrow
		if (GetAsyncKeyState(37))
		{
			velocity = glm::vec2(-1.0f, 0.0f);
			imgState = 1;
		}
		//up
		if (GetAsyncKeyState(38))
		{

			velocity = glm::vec2(0.0f, -1.0f);
			imgState = 2;
		}
		//right
		if (GetAsyncKeyState(39))
		{
			velocity = glm::vec2(1.0f, 0.0f);
			imgState = 1;
		}
		//down
		if (GetAsyncKeyState(40))
		{
			velocity = glm::vec2(0.0f, 1.0f);
			imgState = 3;

		}
		//space
		if (canShoot)
		{
			if (GetAsyncKeyState(32))
			{
				if (timerCount > 10)
				{
					if (beamCount < 20)
					{
						beamCount++;
					}
				}
			}
			else
			{
				if (beamCount > 18)
				{
					//	gun->Shoot(2);
					Shoot(2);
					timerCount = 0;
				}
				if (beamCount < 19 && beamCount > 0)
				{
					//	gun->Shoot(1);
					Shoot(1);
					timerCount = 0;
				}
				beamCount = 0;

			}
		}
		//cntrl
		if (GetAsyncKeyState(17))
		{
			hasGun = false;
			frontGun = false;
		}


		timerCount++;
	}
}

void Player::Move(RECT camerRect)
{
	if (position.x <= camerRect.left + 10)
	{
		position.x = camerRect.left + 11;
	}

	//is the player 
	if (!isKill)
	{
		glm::vec2 tmp = position + velocity * p_Speed;
		if (tmp.x >= camerRect.left && tmp.x <= camerRect.right &&
			tmp.y >= camerRect.top && tmp.y <= camerRect.bottom)
		{
			position += velocity * p_Speed;
		}
		
	}

	if (hasGun)
	{
		if (frontGun)
		{
			gun->position = glm::vec2(position.x + img_Default ->GetWidth(), position.y);
		}
		else
		{
			gun->position = glm::vec2(position.x - gun->image->GetWidth(), position.y);
		}
	}


	//reset veloctity
	velocity = glm::vec2(0.0f, 0.0f);

}

void Player::CheckCollision(std::vector<std::vector<int>> ScreenMap, std::vector<EnemyParent*> Enemys, std::vector<BulletParent*> bullets)
{
	//check if gonna hit object
	glm::vec2 tmp = position;

	int a = (tmp.y + img_Default->GetHeight())  / TILESIZE;
	int b = (tmp.x + img_Default->GetWidth()) / TILESIZE;

	if (ScreenMap[a][b] > 0)
	{
		isKill = true;
	}

	tmp = glm::vec2(b, a);

	for (int i = 0; i < Enemys.size();i++)
	{
		//player hit the enemy
		if (!(GetRect().left >= Enemys[i]->GetRect().right || GetRect().right <= Enemys[i]->GetRect().left ||
			GetRect().top >= Enemys[i]->GetRect().bottom || GetRect().bottom <= Enemys[i]->GetRect().top))
		{
			isKill = true;
			Enemys[i]->isKill = true;
		}
	}
	
	////player hit by bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!(GetRect().left >= bullets[i]->GetRect().right || GetRect().right <= bullets[i]->GetRect().left ||
			GetRect().top >= bullets[i]->GetRect().bottom || GetRect().bottom <= bullets[i]->GetRect().top))
		{
			isKill = true;
			bullets[i]->isKill = true;
		}
	}
	


}

RECT Player::GetRect()
{
	//every image is same size, so pick one
	RECT tmp;
	tmp.left = position.x;
	tmp.top = position.y;
	tmp.right = position.x + img_Default->GetWidth();
	tmp.bottom = position.y + img_Default->GetHeight();

	return tmp;


}

void Player::HandleBullets(RECT cameraRect, std::vector<std::vector<int>> ScreenMap)
{
	for (int j = 0; j < bullets.size(); j++)
	{
		bullets[j]->Update();

		//bullet out map
		if (bullets[j]->isKill)
		{
			delete bullets[j];
			bullets.erase(bullets.begin() + j);
			break;

		}

		//delete bullets out of screen
		if (cameraRect.left >= bullets[j]->GetRect().right || cameraRect.right <= bullets[j]->GetRect().left ||
			cameraRect.top >= bullets[j]->GetRect().bottom || cameraRect.bottom <= bullets[j]->GetRect().top)
		{
			delete bullets[j];
			bullets.erase(bullets.begin() + j);
			break;
		}

		//delete bullets hit walls
		int a = (bullets[j]->position.x + bullets[j]->image->GetWidth()) / TILESIZE;
		int b = (bullets[j]->position.y +( bullets[j]->image->GetHeight() /2 ))/ TILESIZE;

		//0 is nothing
		if (ScreenMap[b][a] != 0 || bullets[j]->isKill)
		{
			delete bullets[j];
			bullets.erase(bullets.begin() + j);
			break;

		}
	}
}


void Player::Shoot(int i)
{
	BulletParent* tmp;

	switch (state)
	{
	case 1:
		if (i == 1){
			tmp = new SmallBullet(screen);
			tmp->position = position;
			tmp->position.x += img_Default->GetWidth();
			bullets.push_back(tmp);
		}
		else if (i == 2)
		{
			tmp = new BigBullet(screen);
			tmp->position = position;
			//tmp->position.x += img_Default->GetWidth();
			bullets.push_back(tmp);
		}
		break;
	case 2:
		//init gun

		if (i == 1){
			if (!hasGun || !frontGun){
				tmp = new SmallBullet(screen);
				tmp->position = position;
				tmp->position.x += img_Default->GetWidth();
				bullets.push_back(tmp);
			}

			BulletParent* tmp = gun->Shoot(1);

			if (hasGun && !frontGun)
			{
				tmp->velocity *= -1;
			}

			bullets.push_back(tmp);

		}
		else if (i == 2)
		{
			tmp = new BigBullet(screen);
			tmp->position = position;
			//tmp->position.x += img_Default->GetWidth();
			bullets.push_back(tmp);
		}
		break;
	case 3:
		//init gun

		if (i == 1){
			if (!hasGun || !frontGun){
				tmp = new SmallBullet(screen);
				tmp->position = position;
				tmp->position.x += img_Default->GetWidth();
				bullets.push_back(tmp);
			}

			BulletParent* tmp = gun->Shoot(1);

			if (hasGun && !frontGun)
			{
				tmp->velocity *= -1;
			}
			bullets.push_back(tmp);

			//bullet up
			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(0.0f, tmp->velocity.x * -1.0f);
			bullets.push_back(tmp);

			//bullet down
			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(0.0f, tmp->velocity.x);
			bullets.push_back(tmp);

		}
		else if (i == 2)
		{
			tmp = new BigBullet(screen);
			tmp->position = position;
			//tmp->position.x += img_Default->GetWidth();
			bullets.push_back(tmp);
		}
		break;
	case 4:
		//init gun

		if (i == 1){
			if (!hasGun || !frontGun){
				tmp = new SmallBullet(screen);
				tmp->position = position;
				tmp->position.x += img_Default->GetWidth();
				bullets.push_back(tmp);
			}

			BulletParent* tmp = gun->Shoot(1);

			if (hasGun && !frontGun)
			{
				tmp->velocity *= -1;
			}
			bullets.push_back(tmp);

			//bullet up
			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(0.0f, tmp->velocity.x * -1.0f);
			bullets.push_back(tmp);

			//bullet down
			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(0.0f, tmp->velocity.x);
			bullets.push_back(tmp);

			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(tmp->velocity.x, -tmp->velocity.x);
			bullets.push_back(tmp);

			tmp = new SmallBullet(screen);
			tmp->position = gun->position;
			tmp->velocity = glm::vec2(tmp->velocity.x, tmp->velocity.x);
			bullets.push_back(tmp);

		}
		else if (i == 2)
		{
			tmp = new BigBullet(screen);
			tmp->position = position;
			//tmp->position.x += img_Default->GetWidth();
			bullets.push_back(tmp);
		}
		break;
	}


}


void Player::HandleGun(RECT cameraRect)
{
	gun->Update(cameraRect);

	if (GetRect().left >= gun->GetRect().right || GetRect().right <= gun->GetRect().left ||
		GetRect().top >= gun->GetRect().bottom || GetRect().bottom <= gun->GetRect().top) {

		// No intersection

	}
	else {

		// Intersection
		hasGun = true;
		if (gun->position.x > position.x + (img_Default->GetWidth() / 2))
		{
			frontGun = true;
		}


	}



}