#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include "State.h"
#include "GameTexture.h"
#include <vector>

class Difficulty : public State
{
	private:
		TTF_Font* font;
		TTF_Font* menuFont;
		std::shared_ptr<GameTexture> title;
		std::vector<std::shared_ptr<GameTexture>> menu;

		void mouseClicked(SDL_Event &e, Engine* engine);

		Difficulty &operator=(const Difficulty&);
		Difficulty(const Difficulty&);

	public:
		Difficulty(MediaCache &mc);
		~Difficulty();

		virtual void enter(Engine* engine);
		virtual void handleEvents(SDL_Event &e, Engine* engine);
		virtual void update(const double dTime, Engine* engine);
		virtual void render();
		virtual void exit(Engine* engine);
};

#endif
