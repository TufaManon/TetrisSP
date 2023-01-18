#include <SDL.h>
#include "game.h"
#include "Controller.h"
SDL_Window *window = nullptr;

Game *Game::game = new Game();

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Game *Game::GetGame()
{
	return game;
}

void Game::Run()
{
	bool quit = false;

	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) == 1)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
}