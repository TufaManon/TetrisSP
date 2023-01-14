#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "../controller/controller.hpp"
#include "../types/types.hpp"
#include "../color/color.hpp"

constexpr auto NO_DEST = "NULL";
class Model
{
	Uint8 jumpFlag;
public:
	virtual void HandleInput(Controller& controller) = 0;
	int GetJumpFlag()
	{
		return jumpFlag;
	}

	void Jump(Uint8 flag)
	{
		jumpFlag = flag;
	}
};



class Interface
{
	SDL_Texture* drawingBoard;
public:
	Interface(SDL_Renderer* renderer)
	{
		drawingBoard = SDL_CreateTexture(renderer, SDL_PixelFormatEnum::SDL_PIXELFORMAT_ARGB8888, SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET, 1600, 900);
		if (drawingBoard == nullptr)
			throw GameError("load tile filed", IMG_GetError());
	}

	~Interface()
	{
		SDL_DestroyTexture(drawingBoard);
	}

	virtual void UpdateInterface(Controller& controller) = 0;
	virtual void RenderDrawBoard(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* target) = 0;
	void RenderDraw(SDL_Renderer* renderer, TTF_Font* font)
	{
		SDL_SetRenderTarget(renderer, drawingBoard);
		SDL_RenderClear(renderer);
		RenderDrawBoard(renderer, font, drawingBoard);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, drawingBoard, NULL, NULL);
	};

	void SetDrawColor(SDL_Renderer* renderer, RGBA rgba)
	{
		SDL_SetRenderDrawColor(renderer, rgba.red, rgba.green, rgba.blue , rgba.alpha * 255);
	}
	
};
		