#pragma once
#include <SDL.h>
#include "../types/types.hpp"
#include <vector>
class Controller
{
public:
    bool left_button_down = false;
    bool right_button_down = false;
    bool soft_down_button_down = false;
    bool hard_down_button_down = false;
    bool lrotate_button_down = false;
    bool rrotate_button_down = false;
    bool swap_button_down = false;
    Vector2D mouseVector;
    
    enum EventType
    {
        empty,
        mouseClick,
        rightClick,
        leftClick,
        downClick,
        softDownClick,
        swapClick,
        lrotateClick,
        rrotateClick
    };

    std::vector<EventType> events;

    void UpdateInstructions(SDL_Event &event)
    {
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON(SDL_BUTTON_LEFT))
                events.push_back(mouseClick);
        }

        else if (event.type == SDL_EventType::SDL_KEYDOWN)
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_A:
                if(left_button_down) break;
                events.push_back(leftClick);
                left_button_down = true;
                break;
            case SDL_SCANCODE_S:
                if (soft_down_button_down) break;
                events.push_back(softDownClick);
                soft_down_button_down = true;
                break;
            case SDL_SCANCODE_D:
                if (right_button_down) break;
                events.push_back(rightClick);
                right_button_down = true;
                break;
            case SDL_SCANCODE_W:
                if (hard_down_button_down) break;
                events.push_back(downClick);
                hard_down_button_down = true;
                break;
            case SDL_SCANCODE_J:
                if (lrotate_button_down) break;
                events.push_back(lrotateClick);
                lrotate_button_down = true;
                break;
            case SDL_SCANCODE_K:
                if (rrotate_button_down) break;
                events.push_back(rrotateClick);
                rrotate_button_down = true;
                break;
            case SDL_SCANCODE_L:
                if (swap_button_down) break;
                events.push_back(swapClick);
                swap_button_down = true;
                break;
            default:
                break;
            }
        }

        else if (event.type == SDL_EventType::SDL_KEYUP)
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_A:
                left_button_down = false;
                break;
            case SDL_SCANCODE_S:
                soft_down_button_down = false;
                break;
            case SDL_SCANCODE_D:
                right_button_down = false;
                break;
            case SDL_SCANCODE_W:

                hard_down_button_down = false;
                break;
            case SDL_SCANCODE_J:

                lrotate_button_down = false;
                break;
            case SDL_SCANCODE_K:

                rrotate_button_down = false;
                break;
            case SDL_SCANCODE_L:

                swap_button_down = false;
                break;
            default:
                break;
            }
        }
    }

    bool MouseClickIn(int x, int y, int w, int h)
    {
        auto it = events.begin();
        while (it != events.end())
        {
            if (*it == mouseClick)
            {
                if (MouseHover(x, y, w, h))
                {
                    it = events.erase(it);
                    return true;
                }
            }

            it++;
        }

        return false;
    }

    bool MouseHover(int x, int y, int w, int h)
    {
        SDL_GetMouseState(&mouseVector.x, &mouseVector.y);
        return mouseVector.x > x && mouseVector.x < x + w && mouseVector.y > y && mouseVector.y < y + h;
    }

    EventType PopEvent()
    {
        EventType res;
        if (events.empty())
            res = empty;
        else
        {
            res = events.back();
            events.pop_back();
        }
        return res;
    }
};