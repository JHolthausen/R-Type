#include "Gui.h"

Gui::Gui(Surface* screen)
{
	this->screen = screen;


	//set the highscore
	string line;

	//Opens file
	ifstream b_file("assets/HighScore.txt");
	//Reads one string from the file
	getline(b_file, line);
	//string to int
	oldHighScore = std::stoi(line);
	//close file stream
	b_file.close();
}

Gui::~Gui()
{
}

void Gui::Update(int score)
{
	this->score = score;
	this->levels = levels;
	HandleHighScore();
	Draw();
}

void Gui::HandleHighScore()
{
	//if the highscore is past current sccore i highscore
	if (oldHighScore < score)
	{
		highScore = score;
	}
	else
	{
		highScore = oldHighScore;
	}
}

void Gui::SaveHighScore()
{
	//open the file for writing
	ofstream a_file("assets/HighScore.txt");
	// save the highscore in file // overwrites
	a_file << highScore << endl;
	// Close the file 
	a_file.close();
}


void Gui::DoEndGame()
{
	screen->Print("Score", SCRWIDTH / 2 - 100, 300, 0xffffff);
	char points[50];

	int n, a = score;
	n = sprintf(points, "%d", a);
	screen->Print(points, SCRWIDTH / 2 - 100, 310, 0xffffff);
	SaveHighScore();
}
void Gui::Draw()
{
	//print highscore
	screen->Print("High Score", SCRWIDTH / 4, 700, 0xffffff);

	char c_highScore[50];

	int n, a = highScore;
	n = sprintf(c_highScore, "%d", a);
	screen->Print(c_highScore, SCRWIDTH / 4, 710, 0xffffff);

	//score text
	screen->Print("Score", SCRWIDTH / 2, 700, 0xffffff);

	//score int
	char points[50];

	a = score;
	n = sprintf(points, "%d", a);
	screen->Print(points, SCRWIDTH / 2, 710, 0xffffff);

	//player lives presented in sprites;
	for (int i = 0; i < lives; i++)
	{
		img->CopyTo(screen, i * img->GetWidth(), SCRHEIGHT - img->GetHeight());
	}

}