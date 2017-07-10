#include "game.h"

#include "Player.h"
#include "LevelHandler.h"
#include "Gui.h"

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>         // std::thread

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff

//Surface imageTest( "assets/ball.png" );
LevelHandler* lh;
Gui* g;

Surface imageTest1("assets/intro.png");
Surface imageTest2("assets/winscreen.png");
Surface imageTest3("assets/lostscreen.png");
Surface imageTest4("assets/black.png");




std::thread* first;


///////////-------------------------
#include "game.h"
#include <string>
#include <iostream>
using namespace std;
#include <windows.h>
using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff
#include <vector>


vector<Surface*> img;
Surface* imageTest;

int crntImg = 0;
Surface* drawBoxImg = new Surface(140, 140);
Surface* drawImg = new Surface(64, 32);

Surface* dragImage = NULL;


HWND hwnd;
string s;
bool isDragging = false;
Sprite* sds;


POINT p;


///////////////-------------------------

//--------------------------
// Threads
//--------------------------
void BackGroundMusic()
{

	PlaySound(TEXT("assets/rainbow"), NULL, SND_LOOP);
}


// -----------------------------------------------------------
// Initialize the game
// -----------------------------------------------------------
void Game::Init()
{
	// game initialization code goes here;
	// will be executed once when app starts

	RECT* t = new RECT();
	hwnd = GetForegroundWindow();

	//g = new Gui(screen);
	state = 0;
	img.push_back(new Surface("assets/Player.png"));
	img.push_back(new Surface("assets/ball.png"));
	img.push_back(new Surface("assets/boom.png"));
	img.push_back(new Surface("assets/charge1.png"));
	img.push_back(new Surface("assets/frog.png"));
	img.push_back(new Surface("assets/rocket.png"));

	imageTest4.CopyTo(drawBoxImg, 0, 0);

	img[0]->CopyTo(drawBoxImg, 0, 0);

	first = new std::thread(BackGroundMusic);
}

// -----------------------------------------------------------
// Main game tick function
// -----------------------------------------------------------
void Game::Tick( float _DT )
{
	//clear screen
	screen->Clear(0);
		
	switch (state)
	{
	case 0:

		//screen->Print("Score", SCRWIDTH / 2, 700, 0xffffff);
		//imageTest1.CopyTo(screen, 0, 0);

		///---------------------------------------------------------------------------
		if (GetAsyncKeyState(38))
		{
			crntImg++;
			Sleep(100);
		}
		if (GetAsyncKeyState(40))
		{
			crntImg--;
			Sleep(100);
		}

		if (crntImg < 0)
		{
			crntImg = img.size() - 1;
		}
		if (crntImg > img.size() - 1)
		{
			crntImg = 0;
		}
		


		imageTest = img[crntImg];

		// clear the canvas
		screen->Clear(0);

		// draw a rectangle

		imageTest1.CopyTo(screen,0, 0);

		drawBoxImg->CopyTo(screen, 36, 360);

		screen->Box(36, 360, 176, 500, 0xff0000);  //draw box


		imageTest->CopyTo(screen, 325, 360); // image
		screen->Box(325, 360, 465, 500, 0xff0000); // select image box

		sds = new Sprite(drawBoxImg, 1);
		imageTest4.CopyTo(drawImg, 0, 0);
		sds->DrawScaled(0,0, 64, 32, drawImg);
		drawImg->CopyTo(screen, 216, 612);
		screen->Box(216, 612, 280, 644, 0xff0000);

		if (GetCursorPos(&p)) {
			//cout << p.x << "," << p.y << "\n";
			cout << s << "\n";
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (ScreenToClient(hwnd, &p))
			{
				//p.x and p.y are now relative to hwnd's client area
				if (p.x >= 325 &&
					p.x <= 465 + imageTest->GetWidth() &&
					p.y >= 360 &&
					p.y <= 500 + imageTest->GetHeight() &&
					!isDragging)
				{
					dragImage = imageTest;
					isDragging = true;
				}
				if (isDragging)
				{
					dragImage->CopyTo(screen, p.x - dragImage->GetWidth() / 2, p.y - dragImage->GetHeight() / 2);
				}


			}

		}
		else
		{
			if (ScreenToClient(hwnd, &p))
			{
				if (p.x >= 36 &&
					p.x <= 176 &&
					p.y >= 360 &&
					p.y <= 500 &&
					isDragging)
				{
					Surface* tmp;

					float a = 36 - (p.x - dragImage->GetWidth() / 2);
					float b = 360 - (p.y - dragImage->GetHeight() / 2);


					dragImage->CopyTo(drawBoxImg, 0 - a, 0 - b);
				}

				isDragging = false;

			}
		}

		//////----------------------------------------------------------------------------------------
		if (GetAsyncKeyState(13))
		{
			state = 1;
		}
		break;
	case 1:
		lh = new LevelHandler(screen);
		g = new Gui(screen);
		state = 2;
		break;
	case 2:
		lh->player->img_Default = drawImg;
		lh->Update();
		lh->Draw();

		g->lives = lh->player->lives;
		g->Update(lh->player->score);

		g->Draw();

		if (lh->player->lives < 1)
		{
			delete lh;
			state = 3;
			break;
		}
		if (lh->levelWon)
		{
			delete lh;
			state = 4;
			break;
		}
		break;
	case 3:

		//screen->Print("u Lost", SCRWIDTH / 2, 700, 0xffffff);
		imageTest3.CopyTo(screen, 0, 0);
		if (GetAsyncKeyState(32))
		{
			state = 0;
			delete g;
		}

		break;
	case 4:
		//screen->Print("Victory", SCRWIDTH / 2, 700, 0xffffff);
		imageTest2.CopyTo(screen, 0, 0);
		g->DoEndGame();
		if (GetAsyncKeyState(32))
		{
			state = 0;
			delete g;
		}

		break;
	}

}