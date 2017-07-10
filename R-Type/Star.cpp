#include "Star.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

//default constructor
Star::Star(Surface* screen)
{
	this->screen = screen;

	//use an random number to set color
	int i = rand() % +3;

	switch (i)
	{
	case 0:
		color = 0xFFFF33;
		break;
	case 1:
		color = 0xFF0000;
		break;
	case 2:
		color = 0x66CCFF;
		break;
	}
	//set star position on random position
	r = rand() % 20;
	position = glm::vec2(1 + rand() % (CAMSCRHEIGHT - 10), 1 + rand() % (CAMSCRHEIGHT - 10));
}

//default destructor
Star::~Star()
{
}

//draw
void Star::Draw(){

	//use r as timer to cause the flickering effect
	if (r < 10){

		screen->Print(".", (int)position.x, (int)position.y, color);

	}
	else if (r < 20)
	{
	}
	else
	{
		r = 0;
	}
	r++;
};