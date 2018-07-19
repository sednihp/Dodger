#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "State.h"
#include "GameTexture.h"
#include <vector>

class HighScore : public State
{
	private:
		TTF_Font* font;
		TTF_Font* font2;
		std::shared_ptr<GameTexture> title;
		std::shared_ptr<GameTexture> mainMenu;
		std::shared_ptr<GameTexture> easy;
		std::shared_ptr<GameTexture> easyScoreTex;
		std::shared_ptr<GameTexture> medium;
		std::shared_ptr<GameTexture> mediumScoreTex;
		std::shared_ptr<GameTexture> hard;
		std::shared_ptr<GameTexture> hardScoreTex;
		std::vector<double> scores;

		void mouseClicked(SDL_Event &e, Engine* engine);
		void loadHighScores();

		HighScore &operator=(const HighScore&);
		HighScore(const HighScore&);

	public:
		HighScore(MediaCache &mc);
		~HighScore();

		virtual void enter(Engine* engine);
		virtual void handleEvents(SDL_Event &e, Engine* engine);
		virtual void update(const double dTime, Engine* engine);
		virtual void render();
		virtual void exit(Engine* engine);
};

#endif