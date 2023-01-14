#include "game.h"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include "model/iModel.hpp"
#include "model/homeModel.hpp"
#include "model/soloModel.hpp"
#include <SDL.h>
#include <SDL_image.h>
Game* Game::game = new Game();

void Game::Init()
{
	auto init_flag = SDL_Init(SDL_INIT_EVERYTHING);
	if (init_flag != 0)
		throw GameError("init was aborted!", SDL_GetError());
	Uint32 windowFlog = SDL_WINDOW_SHOWN;
	if (gConfig.fullScreen)
		windowFlog |= SDL_WINDOW_FULLSCREEN;

	gWindow = SDL_CreateWindow(
		gConfig.gameWindowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gConfig.gameWindowWidth,
		gConfig.gameWindowHeight,
		windowFlog);

	if (gWindow == nullptr)
		throw GameError("create window was aborted!", SDL_GetError());
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

	if (gRenderer == nullptr)
		throw GameError("create renderer was aborted!", SDL_GetError());

	auto ttf_init_flag = TTF_Init();
	if (ttf_init_flag != 0)
		throw GameError("can't init ttf!", TTF_GetError());
	gFont = TTF_OpenFont("assets/font.ttf", 64);
	if (gFont == nullptr)
		throw GameError("can't open font", TTF_GetError());

	auto img_init_flag = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if(img_init_flag == 0)
		throw GameError("can't init img!", IMG_GetError());
	SDL_Surface* bmp = IMG_Load("assets/select.png");
	if (bmp == nullptr) throw GameError("can't open img", SDL_GetError());
}

void Game::Destroy()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_CloseFont(gFont);
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}

void Game::LoadConfigFile()
{

	std::fstream configIf;
	configIf.open("config.yaml", std::ios::in);
	if (configIf.is_open())
	{
		YAML::Node config = YAML::Load(configIf);
		if (config["fullScreen"])
			gConfig.fullScreen = config["fullScreen"].as<bool>();
		if (config["gameWindowHeight"])
			gConfig.gameWindowHeight = config["gameWindowHeight"].as<int>();
		if (config["gameWindowWidth"])
			gConfig.gameWindowWidth = config["gameWindowWidth"].as<int>();
		if (config["gameWindowTitle"])
			gConfig.gameWindowTitle = config["gameWindowTitle"].as<string>();
	}
	else
	{
		configIf.open("config.yaml", std::ios::out | std::ios::trunc);
		if (configIf.is_open())
		{
			YAML::Node config;
			config["fullScreen"] = gConfig.fullScreen;
			config["gameWindowHeight"] = gConfig.gameWindowHeight;
			config["gameWindowWidth"] = gConfig.gameWindowWidth;
			config["gameWindowTitle"] = gConfig.gameWindowTitle;
			configIf << config << std::endl;
		}
		else
			throw GameError("file operation failed!", "unkow error");
	}
}

Game::Game() : gQuitFlag(false)
{
	try
	{
		LoadConfigFile();
	}
	catch (const GameError& e)
	{
		e.PrintError();
	}
}

SDL_Window* Game::GetGameWindow()
{
	return gWindow;
}

SDL_Renderer* Game::GetGameRenderer()
{
	return gRenderer;
}

void Game::Run()
{
	try
	{
		Init();
		Interface* solo = new SoloInterface(gRenderer, gFont);
		while (!gQuitFlag)
		{
			HandleInput();
			solo->UpdateInterface(gController);
			solo->RenderDraw(gRenderer, gFont);
			SDL_RenderPresent(gRenderer);
		}

		delete solo;

	}
	catch (GameError& e)
	{
		e.PrintError();
	}

	Destroy();
}

Game* Game::GetGame()
{
	return game;
}

void Game::HandleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			gQuitFlag = true;
		}

		gController.UpdateInstructions(event);
	}
}