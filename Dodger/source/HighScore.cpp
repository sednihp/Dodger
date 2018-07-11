#include "HighScore.h"
#include "Title.h"
#include "Engine.h"
#include <fstream>
#include <functional>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "CollisionEngine.h"
#include <iterator>
#include <algorithm>
#include <sstream>
#include <iomanip>

HighScore::HighScore(MediaCache& mc) : State(mc),
										font(mediaCache.getFont(50)),
										font2(mediaCache.getFont(80))
{
	title = mediaCache.getText("High Scores", font2, mediaCache.getTextColor());
	title->setPosition(mediaCache.centreX(title->w()), 0);

	mainMenu = mediaCache.getText("Main Menu", font2, mediaCache.getTextColor());
	mainMenu->setPosition(mediaCache.centreX(mainMenu->w()), mediaCache.scrHeight() - mainMenu->h());

	loadHighScores();
}

HighScore::~HighScore()
{
}

void HighScore::enter(Engine*)
{
}

void HighScore::loadHighScores()
{
	std::ifstream inf("files/high scores.txt");

    if(!inf)
    {
		printf("Can't open high scores.txt");
		return;
	}

	//read the scores in from the file and put them in the hiScore vector
	std::copy(std::istream_iterator<double>(inf),
		std::istream_iterator<double>(),
		std::back_inserter(scores));

    inf.close();

	easy = mediaCache.getText("Easy", font2, mediaCache.getTextColor());
	easy->setPosition(mediaCache.centreX(easy->w()), title->h() + 10);

	std::stringstream ss;
	ss << std::fixed << std::setprecision(3) << scores[0];

	easyScoreTex = mediaCache.getText(ss.str(), font, mediaCache.getTextColor());
	easyScoreTex->setPosition(mediaCache.centreX(easyScoreTex->w()), easy->y() + easy->h());
	
	medium = mediaCache.getText("Medium", font2, mediaCache.getTextColor());
	medium->setPosition(mediaCache.centreX(medium->w()), easyScoreTex->y() + easyScoreTex->h() + 10);

	ss.str("");
	ss.clear();
	ss << std::fixed << std::setprecision(3) << scores[1];

	mediumScoreTex = mediaCache.getText(ss.str(), font, mediaCache.getTextColor());
	mediumScoreTex->setPosition(mediaCache.centreX(mediumScoreTex->w()), medium->y() + medium->h());

	hard = mediaCache.getText("Hard", font2, mediaCache.getTextColor());
	hard->setPosition(mediaCache.centreX(hard->w()), mediumScoreTex->y() + mediumScoreTex->h() + 10);

	ss.str("");
	ss.clear();
	ss << std::fixed << std::setprecision(3) << scores[2];

	hardScoreTex = mediaCache.getText(ss.str(), font, mediaCache.getTextColor());
	hardScoreTex->setPosition(mediaCache.centreX(hardScoreTex->w()), hard->y() + hard->h());
}

void HighScore::handleEvents(SDL_Event& e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void HighScore::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
    {
		if(CollisionEngine::checkCollision(mainMenu->rect(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
	}
}

void HighScore::update(const double, Engine*)
{
}

void HighScore::render()
{
	mediaCache.renderTexture(title, title->x(), title->y());

	mediaCache.renderTexture(easy, easy->x(), easy->y());
	mediaCache.renderTexture(easyScoreTex, easyScoreTex->x(), easyScoreTex->y());
	mediaCache.renderTexture(medium, medium->x(), medium->y());
	mediaCache.renderTexture(mediumScoreTex, mediumScoreTex->x(), mediumScoreTex->y());
	mediaCache.renderTexture(hard, hard->x(), hard->y());
	mediaCache.renderTexture(hardScoreTex, hardScoreTex->x(), hardScoreTex->y());

	mediaCache.renderTexture(mainMenu, mainMenu->x(), mainMenu->y());
}

void HighScore::exit(Engine*)
{
}