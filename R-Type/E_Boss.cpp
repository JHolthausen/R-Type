#include "E_Boss.h"
#include "E_BigBullet.h"


using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

E_Boss::E_Boss(Surface* screen)
{
	this->screen = screen;
	xSprites = 3;
	InitTiles();
	InitTail();
	image = new Surface("assets/bos.png");
	isBoss = true;
	hp = 50;
	points = 1000;
}


E_Boss::~E_Boss()
{
}

void E_Boss::Draw(float xx, float yy , glm::vec2 CameraPos)
{
	screenPos = glm::vec2(xx, yy);
	inScreen = true;

	int i = 0;
	int j = 0;
	//draw body;
	
	//draw an new grid with from tiles that are within the grid
	for (int y = 0; y < imageMap.size(); y++)
	{
		for (int x = 0; x < imageMap[y].size(); x++)
		{
			RECT tmpTileRect;
			tmpTileRect.left = x * TILESIZE;
			tmpTileRect.top = y* TILESIZE;
			tmpTileRect.right = x * TILESIZE + TILESIZE;
			tmpTileRect.bottom = y* TILESIZE + TILESIZE;

			RECT tmpImgRect;
			tmpImgRect.left = 0 + bossState* (bossImage->GetWidth() / xSprites);
			tmpImgRect.top = 0;
			tmpImgRect.right = 0 + (bossState + 1)*(bossImage->GetWidth() / xSprites);// , (bossState + 1)*(bossImage->GetWidth() / 3);
			tmpImgRect.bottom = 0 + bossImage->GetHeight();

			if (!(tmpImgRect.left >= tmpTileRect.right || tmpImgRect.right <= tmpTileRect.left ||
				tmpImgRect.top >= tmpTileRect.bottom || tmpImgRect.bottom <= tmpTileRect.top))
			{
			
				Tiles[imageMap[y][x]]->TGraphic->CopyTo(screen, xx + j * TILESIZE, yy + i*TILESIZE );
				
			}

			j++;
			if (j*TILESIZE >= bossImage->GetWidth() / xSprites)
			{
				j = 0;
			}
		}

		i++;
		j = 0;
	}

	// draw monster
	monsterImage->CopyTo(monsterDrawImage, 0 - monsterImage->GetWidth() / 9 * monsterState, 0);
	monsterDrawImage->CopyTo(screen, xx + 370 - monsterImage->GetWidth() / 9, yy + 240);

	//draw tail;
	
	for (int i = 0; i < tail.size(); i++)
	{
		tail[i]->image->CopyTo(screen, tail[i]->position.x - CameraPos.x, tail[i]->position.y - CameraPos.y);
	}

	//draw explosion
	for (int k = 0; k < explosions.size(); k++)
	{
		explosions[k]->Draw();
	}
}
 
void E_Boss::Update(glm::vec2 target)
{
	if (inScreen && !isDying)
	{
		UpdateTimers();
	}

	if (hp <= 0)
	{
		isDying = true;
		HandleDead();
	}


}

void E_Boss::UpdateTimers()
{
	//do next image for animation, if end reverse
	if (monsterTimer >= maxMonsterTimer)
	{
		monsterTimer = 0;
		monsterState += monsterStateMplyr;

		if (monsterState < 0 || monsterState > maxMonsterState)
		{
			monsterStateMplyr *= -1;
			monsterState += monsterStateMplyr;

		}
	}
	monsterTimer++;

	if (bossTimer >= maxBossTimer)
	{
		bossTimer = 0;
		bossState += bossStateMplyr;

		if (bossState < 0 || bossState > maxBossState)
		{
			bossStateMplyr *= -1;
			bossState += bossStateMplyr;
		}
		if (bossState == maxBossState)
		{
			//Shoot(); // mouth open shoot
		}
	}
	bossTimer++;

	if (tailTimer >= maxTailTimer)
	{
		tailTimer = 0;

		HandleTail();
	}
	tailTimer++;

}
//
//void E_Boss::Shot()
//{
//	for (int i = 0; i < maxShotBullets; i++)
//	{
//		bullets.push_back(new E_Boss_Bullet(screen));
//	}
//}

void E_Boss::InitTiles()
{
	//the grid size is image size devided by tilesize

	int width  = bossImage->GetWidth()/TILESIZE;
	int height = bossImage->GetHeight() / TILESIZE;

	//set the size of the 2d vector array
	imageMap.resize(height);

	for (int i = 0; i < height; ++i)
	{
		imageMap[i].resize(width);
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x <width; x++)
		{
			imageMap[y][x] = GrabTile(y, x, bossImage);
			SimpleCnt++;
		}

	}
}


int	E_Boss::GrabTile(int Rows, int Cols, Surface* img)
{

	Tile* T = new Tile();
	img->CopyTo(T->TGraphic, 0 - (Cols * TILESIZE), 0 - (Rows * TILESIZE));


	// T has a graphic
	if (Tiles.size() == 0)
	{
		// there is no doubt this is a new unique graphic to go in
		Tiles.push_back(T);
		TileCounter++;
		return 0;

	}

	else
	{
		for (int i = 0; i < Tiles.size(); i++)
		{
			if (T->Compare(Tiles[i]->TGraphic))
			{ // we found this so it already exists
				delete T;
				T = NULL;
				return i; // the index of the value we found for insertion into that map

			}


		}

		// we competed the loop so that means we found no match.
		Tiles.push_back(T);
		TileCounter++;
		return TileCounter - 1;


	}

	Tiles.push_back(T);
	return SimpleCnt;
}

void E_Boss::HandleTail()
{
	for (int i = 0; i < tail.size(); i++)
	{
		if (i == 0)//head
		{

			tail[i]->position = glm::vec2(pivot.x + r * std::cos(q * t), pivot.y + r * std::sin(q*t));

			if (q > 200 || q < 170)
			{
				cntr *= -1;
			}
			q += cntr;
		}
		else if (i == tail.size() - 1)
		{
		}
		else
		{
			glm::vec2 a = tail[i +1]->position;
			glm::vec2 b = tail[i - 1]->position;
			glm::vec2 c = glm::vec2(2.0f, 2.0f);
			tail[i]->position = a - ((a - b) / c);
			//positions[i] += (positions[i] - positions[i - 1]) / glm::vec2(2.0f, 2.0f);
		}

	}
}

void E_Boss::InitTail()
{
	E_Boss_Tail_Piece* tmp;

	for (int i = 0; i < 20; i++)
	{
		if (i == 0)
		{
			tmp = new E_Boss_Tail_Piece(screen, new Surface("assets/boss/TailHead.png"));
			tmp->position = glm::vec2(13000 + 350/20* i, 550.0f + 0);
			tail.push_back(tmp);
		}
		else
		{
			tmp = new E_Boss_Tail_Piece(screen, new Surface("assets/boss/TailPiece.png"));
			tmp->position = glm::vec2(13000 + 350 / 20 * i, 0550.0f + 0);
			tail.push_back(tmp);
		}
	}

	pivot = glm::vec2(13000 + 350 / 20 * 20, 550.0f + 0);
	q = 180;
	r = 600;
}

void E_Boss::HandleDead() //asuming the boss is within screen
{
	glm:vec2 pos;

	if (!exploding)
	{
		exploding = true;

		for (int i = 0; i < 30; i++)
		{
			int r = rand() % 3;
			pos = glm::vec2(rand() % bossImage->GetWidth() / 3 + screenPos.x, rand() % bossImage->GetHeight());
			switch (r)
			{
			case 0:
				explosions.push_back(new E_Boss_Explosion(screen, new Surface("assets/boss/ExplSheet1.png"), rand() % 30 +1, 6, pos));

				break;
			case 1:	
				explosions.push_back(new E_Boss_Explosion(screen, new Surface("assets/boss/ExplSheet2.png"), rand() % 30 + 1, 3, pos));

				break;
			case 2: 
				explosions.push_back(new E_Boss_Explosion(screen, new Surface("assets/boss/ExplSheet3.png"), rand() % 30 + 1, 6, pos));
				break;
			}
		}



	}
	else
	{
		for (int k = 0; k< explosions.size(); k++)
		{
			if (explosions[k]->Update()) // explosion done, paint part black
			{

				int i = 0;
				int j = 0;
				//get the current tiles on display * wont change
				for (int y = 0; y < imageMap.size(); y++)
				{
					for (int x = 0; x < imageMap[y].size(); x++)
					{
						RECT tmpTileRect;
						tmpTileRect.left = x * TILESIZE;
						tmpTileRect.top = y* TILESIZE;
						tmpTileRect.right = x * TILESIZE + TILESIZE;
						tmpTileRect.bottom = y* TILESIZE + TILESIZE;

						RECT tmpImgRect;
						tmpImgRect.left = 0 + bossState* (bossImage->GetWidth() / 3);
						tmpImgRect.top = 0;
						tmpImgRect.right = 0 + (bossState + 1)*(bossImage->GetWidth() / 3);// , (bossState + 1)*(bossImage->GetWidth() / 3);
						tmpImgRect.bottom = 0 + bossImage->GetHeight();

						RECT explosionRect;
						explosionRect.left = 0 + bossState* (bossImage->GetWidth() / 3);
						explosionRect.top = 0;
						explosionRect.right = 0 + (bossState + 1)*(bossImage->GetWidth() / 3);// , (bossState + 1)*(bossImage->GetWidth() / 3);
						explosionRect.bottom = 0 + bossImage->GetHeight();

						if (!(tmpImgRect.left >= tmpTileRect.right || tmpImgRect.right <= tmpTileRect.left || // is tile in curent image
							tmpImgRect.top >= tmpTileRect.bottom || tmpImgRect.bottom <= tmpTileRect.top))
						{

							if (!(explosionRect.left >= tmpTileRect.right || explosionRect.right <= tmpTileRect.left || // is tile in explosion
								explosionRect.top >= tmpTileRect.bottom || explosionRect.bottom <= tmpTileRect.top))
							{
								imageMap[y][x] = 0;
							}
						}

						j++;

						if (j*TILESIZE >= bossImage->GetWidth() / 3)
						{
							j = 0;
						}
					}

					i++;
					j = 0;
				}


				//delete explosion
				delete explosions[k];
				explosions.erase(explosions.begin() + k);

			}
		}
	}

	if (explosions.size() <= 0)
	{
		isKill = true;
	}
}

BulletParent* E_Boss::Shoot(glm::vec2 target)
{

	if (!isDying){
	shootCounter++;
	jk++;
	if (!(GetAgroRect().left >= target.x || GetAgroRect().right <= target.x ||
		GetAgroRect().top >= target.y || GetAgroRect().bottom <= target.y))
	{
		if (shootCounter > maxShootCounter + 20)
		{
			shootCounter = 0;
		}
		if (shootCounter > maxShootCounter && jk > 3)
		{
			jk = 0;
			BulletParent* tmp = new E_BigBullet(screen);

			glm::vec2 t;
			t.y = target.y - (position.y + image->GetHeight() / 2);
			t.x = target.x - (position.x + image->GetWidth() / 2);

			int d = std::sqrt(pow(t.x, 2) + pow(t.y, 2));


			//normalize vector
			tmp->velocity.y = t.y / d;
			tmp->velocity.x = t.x / d;

			tmp->position.x = position.x + image->GetWidth() / 2;
			tmp->position.y = position.y + image->GetHeight() / 2;
			return tmp;
		}


	}


	}
	return NULL;


}

RECT E_Boss::GetAgroRect()
{
	int a = 10000;

	RECT tmp;
	tmp.left = position.x - a;
	tmp.top = position.y - a;
	tmp.right = position.x + image->GetWidth();
	tmp.bottom = position.y + image->GetHeight();

	return tmp;
}