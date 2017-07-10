#pragma once

#include "EnemyParent.h"
#include "Tile.h"

namespace Tmpl8{
	class EnemyGroundBot : public EnemyParent
	{
	public:
		EnemyGroundBot(Surface* screen, std::vector<std::vector<int>> ScreenMap);
		~EnemyGroundBot();

		void Draw(float x, float y, glm::vec2 camPos);
		void Update(glm::vec2 target);

		void CheckMove();



		int shootCounter;
		int imgState;
		int cntr;
		std::vector<std::vector<int>> ScreenMap;


	};

}