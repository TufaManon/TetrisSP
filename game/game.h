#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "types/types.hpp"
#include "controller/controller.hpp"
using std::string;



class Resource
{
    
};




class Game
{
private:
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    TTF_Font *gFont;
    GameConfig gConfig;
    Controller gController;
    Game();
    void Init();
    void Destroy();
    bool gQuitFlag;
    static Game *game;
    void LoadConfigFile();
    void HandleInput();
public:

    SDL_Window *GetGameWindow();
    SDL_Renderer *GetGameRenderer();

    void Run();
    static Game *GetGame();
    // delete auto generated func
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
};