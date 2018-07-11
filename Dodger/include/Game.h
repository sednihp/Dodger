#ifndef GAME_H
#define GAME_H

#include "State.h"
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"

class Game : public State
{
	private:
		TTF_Font* font;
		Player player;
		std::vector<std::unique_ptr<Enemy>> enemies;
		unsigned int maxEnemySpeed, minEnemySpeed;
		int maxEnemyDim, minEnemyDim;
		Timer timer, addEnemyTimer;
		std::shared_ptr<GameTexture> clock;
		std::shared_ptr<GameTexture> gameOverTex;
		std::shared_ptr<GameTexture> scoreTex;
		std::shared_ptr<GameTexture> highScoreTex;
		std::shared_ptr<GameTexture> restartTex;
		int difficulty, startEnemyCount;
		std::vector<double> highScores;
		bool newHighScore, paused;
		
		void keyPressed(SDL_Event& e, Engine* engine);
		void mouseClicked(SDL_Event&, Engine* engine);
		void createEnemy(Engine* e);
		const std::string getClockTime();
		void setDifficulty();
		void gameOver();
		const bool checkNewHighScore();

	public:
		Game(MediaCache& mc, int difficulty);
		~Game();

		void enter(Engine* engine);
		void handleEvents(SDL_Event& e, Engine* engine);
		void update(const double dTime, Engine* engine);
		void render();
		void exit(Engine* engine);
};

#endif
