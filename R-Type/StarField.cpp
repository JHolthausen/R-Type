#include "Starfield.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

StarField::StarField(Surface* scrn)
{
	screen = scrn;

	//create first
	n = new noded;
	n->star = new Star(screen);
	n->prev = NULL;


	head = n;
	tail = n;

	for (int i = 1; i < starAmount; i++){
		CreateStars();
	}
}

StarField::~StarField()
{
}

void StarField::CreateStars()
{
	n = new noded;
	n->star = new Star(screen);
	n->prev = tail;




	tail->next = n;
	tail = n;
	tail->next = NULL;
}

void StarField::Update()
{
	noded* temp = head;

	while (temp != NULL)
	{
		if (temp->star->position.x > SCRWIDTH - 10)
		{
			temp->star->position = glm::vec2(1,1 + rand() % (SCRHEIGHT - 10));
		}
		else
		{
			temp->star->position += temp->star->velocity;
		}

		//temp->star->Update();
		temp = temp->next;
	}
	Draw();
}

void StarField::Draw()
{
	noded* temp = head;

	while (temp != NULL)
	{
		temp->star->Draw();
		temp = temp->next;
	}
}