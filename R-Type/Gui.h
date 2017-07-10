#pragma once

#include <string>
#include <iostream>
#include <stdio.h>

#include <fstream>

#include "template.h"
#include "surface.h"
#include "game.h"
using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff
using namespace std;

namespace Tmpl8 {
	class Gui
	{
	public:
		Gui(){};
		Gui( Surface* screen);
		~Gui();
		void Draw();
		void Update(int score);
		void DoEndGame();
		void SaveHighScore();
		void HandleHighScore();

		int oldHighScore;
		int highScore = 0;
		int lives = 3, score = 0, levels;
		std::string lifeString, scoreString;
		Surface* screen;

		int i = 0;
		bool startGame = false;

		Surface* img = new Surface("assets/p.png");
	};
};