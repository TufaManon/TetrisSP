#pragma once
#include <SDL.h>
#include <vector>

class Animation
{
    uint64_t duration;
    std::vector<SDL_Texture *> textures;
    bool loop;
    bool play;

    uint64_t timeConter;
    uint64_t currentTime;
public:
    Animation(SDL_Texture* texs[], int len, uint64_t dur)
    {
        duration = dur;
        for(int i = 0; i < len; i++)
        {
            textures.push_back(texs[i]);
        }
        Reset();
    }
    ~Animation()
    {
        Destroy();
    }
    SDL_Texture *Play()
    {
        if(!play)
        {
            play = true;
            currentTime = SDL_GetTicks64();
        } 
        auto now = SDL_GetTicks64();
        timeConter += now - currentTime;
        currentTime = now;

        if (timeConter >= duration && !loop)
        {
            Reset();
            return textures.back();
        }

        else
            return textures.at((timeConter / (duration / textures.size())) % (textures.size() - 1));
    }

    void Reset()
    {
        play = false;
        timeConter = 0;
    }

    bool Playing()
    {
        return false;
    }

    void Destroy()
    {
        for(auto it = textures.begin(); it != textures.end(); it++)
        {
            SDL_DestroyTexture(*it);
        }
    }
};
