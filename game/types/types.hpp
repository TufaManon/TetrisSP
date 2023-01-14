#pragma once
#include <ctime>
#include <string>
using  std::string;

struct Vector2D
{
    int x, y;
    Vector2D()
    {
        x = y = 0;
    }
    Vector2D(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    const Vector2D operator+(const Vector2D& right) const
    {
        return Vector2D(right.x + x, right.y + y);
    }

    const Vector2D operator-(const Vector2D& right) const
    {
        return Vector2D(x - right.x, y - right.y);
    }

    const Vector2D& operator--(int i)
    {
        this->x -= i;
        this->y -= i;
        return *this;
    }
};
class GameError
{
    string sdlErrorMessage;
    string errorMessage;
    string timeStamp;

public:
    GameError(const char *message, const char *sdlMessage) : errorMessage(message), sdlErrorMessage(sdlMessage)
    {
        time_t now = time(0);
        timeStamp = ctime(&now);
    }

    void PrintError() const
    {
        SDL_Log(">> %s :error happened -- %s,error detail message is %s", timeStamp.c_str(), errorMessage.c_str(), sdlErrorMessage.c_str());
    }
};

struct GameConfig
{
    int gameWindowHeight = 1080 / 2;
    int gameWindowWidth = 1920 / 2;
    string gameWindowTitle = "tetris";
    bool fullScreen = false;
};