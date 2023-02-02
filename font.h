//
// Created by Tufa Manon on 2023/1/30.
//

#ifndef TETRIS_FONT_H_
#define TETRIS_FONT_H_
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class Font {
 public:
  Font(std::string txt, TTF_Font *font, SDL_Color color);
  ~Font();
  void SetTxt(std::string txt);
  SDL_Texture *GetTexture(SDL_Renderer *renderer);
  SDL_Color color_;
  int GetH() const;
  int GetW() const;

 private:
  std::string txt_;
  TTF_Font *font_;
  SDL_Texture *texture_ = nullptr;
  bool re_draw_;
  int h_ = 0, w_ = 0;
};

#endif//TETRIS_FONT_H_
