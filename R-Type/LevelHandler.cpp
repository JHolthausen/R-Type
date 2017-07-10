#include "LevelHandler.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

Surface* tempsurf;

Sprite* previewImg;
int h = 0;

LevelHandler::LevelHandler(Surface* screen)
{
	this->screen = screen;
	player = new Player(screen);
	InitLevels();
	stars = new StarField(screen);

	tempsurf = new Surface(14272, 640);

	for (int y = 0; y < levels[crntLvl - 1]->ScreenMap.size(); y++)
	{
		for (int x = 0; x < levels[crntLvl - 1]->ScreenMap[y].size(); x++)
		{
			Tiles[levels[crntLvl - 1]->ScreenMap[y][x]]->TGraphic->CopyTo(tempsurf, x*TILESIZE, y*TILESIZE);
		}
	}

	previewImg = new Sprite(tempsurf, 1);// imageTest;/// new Sprite(1);
}


LevelHandler::~LevelHandler()
{
}




void LevelHandler::InitLevels()
{
	//place the maps in the map with an int index
	levels.push_back(new Level1(screen));


	//get al the maps tiles
	for each(LevelParent* lvl in levels)
	{
		for (int y = 0; y < (lvl->image->GetHeight() / TILESIZE); y++)
		{
			for (int x = 0; x <(lvl->image->GetWidth() / TILESIZE); x++)
			{
				lvl->ScreenMap[y][x] = GrabTile(y, x, lvl->image);
			}

		}
	}
	
	levels[crntLvl - 1]->InitEnemys();

}


int	LevelHandler::GrabTile(int Rows, int Cols, Surface* img)
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


void LevelHandler::Draw()
{
	stars->Draw();

	cameraRect.left = cameraPos.x;
	cameraRect.top = cameraPos.y;
	cameraRect.right = cameraPos.x + CAMSCRWIDTH ;
	cameraRect.bottom = cameraPos.y + CAMSCRHEIGHT ;

	int i = 0;
	int j = 0;
	//draw an new grid with from tiles that are within the grid
	for (int y = 0; y < levels[crntLvl - 1]->ScreenMap.size(); y++)
	{
		for (int x = 0; x < levels[crntLvl - 1]->ScreenMap[y].size(); x++)
		{
			RECT tmp;
			tmp.left = x * TILESIZE;
			tmp.top = y* TILESIZE;
			tmp.right = x * TILESIZE + TILESIZE;
			tmp.bottom = y* TILESIZE + TILESIZE;

			if (!(cameraRect.left >= tmp.right || cameraRect.right <= tmp.left ||
				cameraRect.top >= tmp.bottom || cameraRect.bottom <= tmp.top))
			{
				if (levels[crntLvl - 1]->ScreenMap[y][x] > 0)
				{
					Tiles[levels[crntLvl - 1]->ScreenMap[y][x]]->TGraphic->CopyTo(screen, j * TILESIZE - cameraPos.x, i*TILESIZE - cameraPos.y);
				}
			}

			j++;
		}

		i++;
		j = 0;

	}



	//draw the enemys that are in screen
	for each(EnemyParent* enemy in levels[crntLvl - 1]->enemys)
	{
		//sidescrolling only x needed
		if (enemy->position.x > cameraPos.x &&
			enemy->position.x < cameraPos.x + CAMSCRWIDTH)
		{
			float a = enemy->position.x - cameraPos.x;
			float b = enemy->position.y - cameraPos.y;
			enemy->Draw(a, b, cameraPos);
		}
	}
	
	//draw the player
	float a = player->position.x - cameraPos.x;
	float b = player->position.y - cameraPos.y;
	player->Draw(a, b);


	//draw the bullets in screen
	for each(BulletParent* bullet in levels[crntLvl - 1]->bullets)
	{
		//sidescrolling only x needed
		if (bullet->position.x > cameraPos.x &&
			bullet->position.x < cameraPos.x + CAMSCRWIDTH)
		{
			float a = bullet->position.x - cameraPos.x;
			float b = bullet->position.y - cameraPos.y;
			bullet->Draw(a, b);
		}
	}

	for each(BulletParent* bullet in player->bullets)
	{
		//sidescrolling only x needed
		if (bullet->position.x > cameraPos.x &&
			bullet->position.x < cameraPos.x + CAMSCRWIDTH)
		{
			float a = bullet->position.x - cameraPos.x;
			float b = bullet->position.y - cameraPos.y;
			bullet->Draw(a, b);
		}
	}

	for each(PowerUp* power in  levels[crntLvl - 1]->powers)
	{
		//sidescrolling only x needed
		if (power->position.x > cameraPos.x &&
			power->position.x < cameraPos.x + CAMSCRWIDTH)
		{
			float a = power->position.x - cameraPos.x;
			float b = power->position.y - cameraPos.y;
			power->Draw(a, b);
		}
	}


	if (!player->createGun)
	{
		if (player->gun->position.x > cameraPos.x &&
			player->gun->position.x < cameraPos.x + CAMSCRWIDTH)
		{
			float a = player->gun->position.x - cameraPos.x;
			float b = player->gun->position.y - cameraPos.y;
			player->gun->Draw(a, b);
		}
	}


	//---------------------------------
	//draw minimap
	
	//previewImg->DrawScaled(0, SCRHEIGHT - 100, 1784, 100, screen);

	//// draw a filled rectangle -- gives erre halfway
	//a = (cameraPos.x);
	//b = SCRHEIGHT - 100;
	//screen->Bar(a, b, a + 5, SCRHEIGHT, 0x0000ff);

}


void LevelHandler::Update()
{

	stars->Update();

	if (cameraPos.x + CAMSCRWIDTH < levels[crntLvl - 1]->image->GetWidth())
	{
		if (!(cameraPos.x >= 12500))
		{
			cameraPos += glm::vec2(1.0f, 0.0f) * scrollSpeed;
		}
		if (levels[crntLvl - 1]->bosDead)
		{
			cameraPos += glm::vec2(1.0f, 0.0f) * scrollSpeed;
			player->canShoot = false;

		}

	}

	if (player->position.x >= 14000)
	{
		levelWon = true;
	}
		levels[crntLvl - 1]->Update(player, cameraRect);

		PlayerDead();
		player->Update(levels[crntLvl - 1]->ScreenMap, levels[crntLvl - 1]->enemys, cameraRect, levels[crntLvl - 1]->bullets);
}

void LevelHandler::PlayerDead()
{
	if (player->isKill)
	{ 
		p_score = player->score;
		p_lives++;
		player->lives -= p_lives;

		if (p_lives < 3){
			while (!(GetAsyncKeyState(13)))
			{/*
				screen->Clear(0);
				screen->Print("Press Enter", 300, 300, 0xffffff);*/
			}
		}

		cameraPos = glm::vec2(0.0f, 0.0f); // use this to move on the grid
		delete player;
		player = new Player(screen);
		player->lives -= p_lives;
		player->score = p_score - 100; // score -100, u died


		cameraRect.left = cameraPos.x;
		cameraRect.top = cameraPos.y;
		cameraRect.right = cameraPos.x + CAMSCRWIDTH;
		cameraRect.bottom = cameraPos.y + CAMSCRHEIGHT;
	}
}
