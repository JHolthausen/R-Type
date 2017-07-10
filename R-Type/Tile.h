#pragma once
#include "game.h"

#define TILESIZE 20

namespace Tmpl8
{
	//stupidly simple class to store a tile
	class Tile
	{
	public:
		Tile();
		~Tile();

		void Draw(int x, int y, Surface* ScreenToDrawTo);  // ok drawing is this things main function
		bool Compare(Surface* CompareWith);

		// it really only needs 
		Surface*	TGraphic;
	};

};

