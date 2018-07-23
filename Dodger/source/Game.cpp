#include "Game.h"
#include "Title.h"
#include "Util.h"
#include "CollisionEngine.h"
#include "Engine.h"
#include "Difficulty.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

Game::Game(MediaCache &mc, int d) : State(mc),
									font(mediaCache.getFont(60)),
									player(mediaCache.scrWidth(), mediaCache.scrHeight()),
									maxEnemySpeed(300), minEnemySpeed(50), minEnemyDim(10), maxEnemyDim(60),
									timer(), difficulty(d), startEnemyCount(5*difficulty),
									paused(false)
{
	clock = mediaCache.getText(getClockTime(), mediaCache.getFont(50), mediaCache.getTextColor());

	setDifficulty();

	highScoreTex = mediaCache.getText("New High Score", mediaCache.getFont(80), mediaCache.getTextColor());
	highScoreTex->setPosition(mediaCache.centreX(highScoreTex->w()), mediaCache.centreY(highScoreTex->h()) + highScoreTex->h());

	restartTex = mediaCache.getText("Play Again", mediaCache.getFont(80), mediaCache.getTextColor());
	restartTex->setPosition(mediaCache.centreX(restartTex->w()), mediaCache.scrHeight() - restartTex->h());
}

Game::~Game()
{
}

// ===============
// State functions
// ===============

void Game::enter(Engine* e)
{
	for (int i = 0; i < startEnemyCount; ++i) 
	{
		createEnemy(e);
	}
	timer.start();
	addEnemyTimer.start();
}

void Game::handleEvents(SDL_Event &e, Engine* engine)
{
	keyPressed(e, engine);
	mouseClicked(e, engine);
}

void Game::update(const double deltaTime, Engine* e)
{
	if (player.isAlive() && !paused)
	{
		player.move(mediaCache.scrWidth(), mediaCache.scrHeight(), deltaTime);

		//for every enemy:
		//first check it is alive, then move it, then check if it overlaps the player
		//if it isn't alive, recreate a new enemy in it's place
		for (auto &enemy : enemies)
		{
			if (enemy->isAlive())
			{
				enemy->move(mediaCache.scrHeight(), deltaTime);

				if (CollisionEngine::checkCollision(enemy->getBox(), player.getBox()))
				{
					player.kill();
					timer.pause();
					gameOver();
				}
			}
			else
			{
				unsigned int dimension = e->getRandom(minEnemyDim, maxEnemyDim);
				unsigned int x = e->getRandom(0, mediaCache.scrWidth() - dimension);
				unsigned int speed = e->getRandom(minEnemySpeed, maxEnemySpeed);

				enemy = std::make_unique<Enemy>(x, speed, dimension);
			}
		}

		if (addEnemyTimer.getSeconds() > 1 && static_cast<int>(addEnemyTimer.getSeconds()) % 5 == 0)
		{
			createEnemy(e);
			addEnemyTimer.restart();
		}

		clock = mediaCache.getText(getClockTime(), mediaCache.getFont(50), mediaCache.getTextColor());
	}
}

void Game::render()
{
	mediaCache.drawRectangle(player.getBox(), player.getColor());

	for (auto &enemy : enemies)
	{
		if (enemy->isAlive())
		{
			mediaCache.drawRectangle(enemy->getBox(), enemy->getColor());
		}
	}

	mediaCache.renderTexture(clock, 0, 0);

	if (!player.isAlive())
	{
		mediaCache.renderTexture(gameOverTex, gameOverTex->x(), gameOverTex->y());
		mediaCache.renderTexture(scoreTex, scoreTex->x(), scoreTex->y());

		if (newHighScore)
		{
			mediaCache.renderTexture(highScoreTex, highScoreTex->x(), highScoreTex->y());
		}

		mediaCache.renderTexture(restartTex, restartTex->x(), restartTex->y());
	}
}


void Game::exit(Engine*)
{

}

// ===============
// Class functions
// ===============

const std::string Game::getClockTime()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(3) << timer.getSeconds();
	return ss.str();
}

void Game::setDifficulty()
{
	switch (difficulty)
	{
	case 1: maxEnemySpeed = 250;
		minEnemySpeed = 50;
		minEnemyDim = 10;
		maxEnemyDim = 50;
		break;
	case 2:
	default: maxEnemySpeed = 300;
		minEnemySpeed = 50;
		minEnemyDim = 10;
		maxEnemyDim = 60;
		break;
	case 3: maxEnemySpeed = 400;
		minEnemySpeed = 100;
		minEnemyDim = 20;
		maxEnemyDim = 80;
		break;
	}
}

void Game::createEnemy(Engine* e)
{
	unsigned int dimension = e->getRandom(minEnemyDim, maxEnemyDim);
	unsigned int x = e->getRandom(0, mediaCache.scrWidth() - dimension);
	unsigned int speed = e->getRandom(minEnemySpeed, maxEnemySpeed);

	enemies.push_back(std::make_unique<Enemy>(x, speed, dimension));
}

void Game::keyPressed(SDL_Event &event, Engine*)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_SPACE:
			{
				paused = !paused;
				if (timer.isPaused())
				{
					timer.unpause();
				}
				else
				{
					timer.pause();
				}
			}
			break;
			case SDLK_RIGHT:
				player.setDirection({ 1, 0 });
				break;

			case SDLK_LEFT:
				player.setDirection({ -1, 0 });
				break;

			case SDLK_UP:
				player.setDirection({ 0, -1 });
				break;

			case SDLK_DOWN:
				player.setDirection({ 0, 1 });
				break;

			default: break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
			player.setDirectionX(0);
			break;

		case SDLK_UP:
		case SDLK_DOWN:
			player.setDirectionY(0);
			break;

		default: break;
		}
	}
}

void Game::mouseClicked(SDL_Event&, Engine* engine)
{
	int x, y;
	if (SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
	{
		if (CollisionEngine::checkCollision(restartTex->rect(), x, y))
		{
			if (!player.isAlive())
			{
				engine->changeState(std::make_shared<Difficulty>(mediaCache));
			}
		}
	}
}

void Game::gameOver()
{
	gameOverTex = mediaCache.getText("Game Over", mediaCache.getFont(80), mediaCache.getTextColor());
	gameOverTex->setPosition(mediaCache.centreX(gameOverTex->w()), mediaCache.centreY(gameOverTex->h()) - gameOverTex->h());

	std::string score = "Score: " + getClockTime();

	scoreTex = mediaCache.getText(score, mediaCache.getFont(80), mediaCache.getTextColor());
	scoreTex->setPosition(mediaCache.centreX(scoreTex->w()), mediaCache.centreY(scoreTex->h()));

	newHighScore = checkNewHighScore();
}

const bool Game::checkNewHighScore()
{
	std::ifstream myfile("files/high scores.txt");

	if (!myfile)
	{
		throw("Could not open high scores");
	}

	std::copy(std::istream_iterator<double>(myfile),
		std::istream_iterator<double>(),
		std::back_inserter(highScores));

	myfile.close();

	double score = std::stod(getClockTime());
	bool checkHighScore = false;

	if (score > highScores[difficulty - 1])
	{
		highScores[difficulty - 1] = score;
		checkHighScore = true;

		std::ofstream ofs("files/high scores.txt");

		if (!ofs)
		{
			throw("Could not open high scores");
		}

		for (auto &hiScore : highScores)
		{
			ofs << hiScore << std::endl;
		}

		ofs.close();
	}

	return checkHighScore;
}