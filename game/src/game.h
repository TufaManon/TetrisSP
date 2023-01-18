#pragma once

class Game
{
private:
    Game();
    static Game *game;
public:
    ~Game();
    void Run();
    static Game *GetGame();
    // delete auto generated func
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
};