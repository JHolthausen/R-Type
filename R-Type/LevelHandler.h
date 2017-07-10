#pragma once

#include "template.h"
#include "surface.h"

#include "Tile.h"

#include "game.h"
#include "LevelParent.h"
#include "Level1.h"
#include <vector>
#include "Player.h"
#include "EnemyCircle.h"
#include "Player.h"
#include "PowerUp.h"
#include "StarField.h"


namespace Tmpl8{
	class LevelHandler
	{
	public:
		LevelHandler(Surface* screen);
		~LevelHandler();

		void InitLevels();
		int GrabTile(int Rows, int Cols, Surface* img);
		void Draw();
		void Update();
		void PlayerDead();

		virtual void InitEnemys(){};

		Surface* screen;

		//use an map to store the maps
		std::vector<LevelParent*> levels;

		int crntLvl = 1;

		RECT cameraRect;
		int	ScreenMap[CAMSCRHEIGHT / TILESIZE][CAMSCRWIDTH / TILESIZE ];

		glm::vec2 cameraPos = glm::vec2(0.0f, 0.0f); // use this to move on the grid
		bool levelWon = false;

		std::vector<Tile*> Tiles;
		int	SimpleCnt = 0;
		int TileCounter = 0;


		glm::vec2 scrollSpeed = glm::vec2(3.0f, 3.0f);

		std::vector<PowerUp*> powers;

		//player
		Player* player;
		StarField* stars;


		int p_lives = 0;
		int p_score = 0;

	};

}