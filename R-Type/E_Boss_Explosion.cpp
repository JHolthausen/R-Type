#include "E_Boss_Explosion.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff



E_Boss_Explosion::E_Boss_Explosion(Surface* screen, Surface* Image, int maxTimer, int sprites, glm::vec2 Position)
{
	this->screen = screen;
	this->image = Image;
	this->maxTimer = maxTimer;
	this->sprites = sprites;
	this->Position = Position;

	width = image->GetWidth() / sprites;
	height = image->GetHeight();

	drawImage = new Surface(width, height);

}


E_Boss_Explosion::~E_Boss_Explosion()
{
}


bool E_Boss_Explosion::Update()
{
	return UpdateTimers();
}

bool E_Boss_Explosion::UpdateTimers()
{
	if (this->timer >= maxTimer)
	{
		this->timer = 0;
		state += 1;

		if (state > sprites)
		{
			return true;
		}
	}
	this->timer++;
	return false;
}
void E_Boss_Explosion::Draw()
{
	image->CopyTo(drawImage, 0 - width * state, 0);
	drawImage->CopyTo(screen, Position.x, Position.y);
}