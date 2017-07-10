#pragma once
#include "EnemyParent.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8 {

	class E_Boss_Tail_Piece : public EnemyParent
	{
	public:
		E_Boss_Tail_Piece(Surface* screen, Surface* image);
		~E_Boss_Tail_Piece();

		void Draw(float x, float y){}
		void Update(){};


	};

}