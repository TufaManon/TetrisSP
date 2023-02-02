//
// Created by Tufa Manon on 2023/1/30.
//

#include "font.h"

#include <utility>
Font::Font(std::string txt, TTF_Font *font, SDL_Color color) : txt_(std::move(txt)), font_(font), color_(color) {
  re_draw_ = true;
}
void Font::SetTxt(std::string txt) {
  txt_ = std::move(txt);
  re_draw_ = true;
}
SDL_Texture *Font::GetTexture(SDL_Renderer *renderer) {
  if (!re_draw_) return texture_;
  SDL_Surface *blended = TTF_RenderUTF8_Blended(font_, txt_.c_str(), color_);
  w_ = blended->w;
  h_ = blended->h;
  SDL_DestroyTexture(texture_);
  texture_ = SDL_CreateTextureFromSurface(renderer, blended);
  re_draw_ = false;
  SDL_FreeSurface(blended);
  return texture_;
}
Font::~Font() {
  SDL_DestroyTexture(texture_);
}
int Font::GetH() const {
  return h_;
}
int Font::GetW() const {
  return w_;
}
