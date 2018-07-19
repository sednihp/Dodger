#include "Difficulty.h"
#include "Title.h"
#include "Game.h"
#include "Engine.h"
#include "HighScore.h"
#include "CollisionEngine.h"
#include <iostream>
#include <fstream>

Difficulty::Difficulty(MediaCache &mc) : State(mc), 
								font(mediaCache.getFont(200)),
								menuFont(mediaCache.getFont(100))
{
	SDL_Color c = mediaCache.getTextColor();
	title = mediaCache.getText("Dodger", font, c);
	title->setPosition(mediaCache.centreX(title->w()), 0);

	menu.push_back(mediaCache.getText("Easy", menuFont, c));
	menu.push_back(mediaCache.getText("Medium", menuFont, c));
	menu.push_back(mediaCache.getText("Hard", menuFont, c));
	menu.push_back(mediaCache.getText("Main Menu", menuFont, c));

	for(size_t i=0; i<menu.size(); ++i)
	{
		menu[i]->setPosition(mediaCache.centreX(menu[i]->w()), mediaCache.centreY(menu[i]->h()) + i*menu[i]->h() - menu[i]->h()/2);
	}
}

Difficulty::~Difficulty()
{
}

void Difficulty::enter(Engine*)
{
}

void Difficulty::handleEvents(SDL_Event &e, Engine* engine)
{
	if(e.type == SDL_MOUSEBUTTONDOWN)
	{
		mouseClicked(e, engine);
	}
}

void Difficulty::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
    {
		if(CollisionEngine::checkCollision(menu[0]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Game>(mediaCache, 1));
		}
		else if (CollisionEngine::checkCollision(menu[1]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Game>(mediaCache, 2));
		}
		else if (CollisionEngine::checkCollision(menu[2]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Game>(mediaCache, 3));
		}
		else if (CollisionEngine::checkCollision(menu[3]->rect(), x, y))
		{
			engine->changeState(std::make_shared<Title>(mediaCache));
		}
	}
}

void Difficulty::update(const double, Engine*)
{
}

void Difficulty::render()
{
	mediaCache.renderTexture(title, title->x(), title->y());

	for(auto &item : menu)
	{
		mediaCache.renderTexture(item, item->x(), item->y());
	}
}

void Difficulty::exit(Engine* )
{

}