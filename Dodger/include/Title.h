#ifndef TITLE_H
#define TITLE_H

#include "State.h"
#include "GameTexture.h"
#include <vector>

class Title : public State
{
	private:
		TTF_Font* font;
		TTF_Font* menuFont;
		std::shared_ptr<GameTexture> title;
		std::vector<std::shared_ptr<GameTexture>> menu;

		void mouseClicked(SDL_Event &e, Engine* engine);

		Title &operator=(const Title&);
		Title(const Title&);

	public:
		Title(MediaCache &mc);
		~Title();

		virtual void enter(Engine* engine);
		virtual void handleEvents(SDL_Event &e, Engine* engine);
		virtual void update(const double dTime, Engine* engine);
		virtual void render();
		virtual void exit(Engine* engine);
};

#endif
