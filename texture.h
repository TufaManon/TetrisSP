//
// Created by Tufa Manon on 2023/1/27.
//

#ifndef TETRIS_TEXTURE_H_
#define TETRIS_TEXTURE_H_
#include "SDL.h"
class Texture {
 public:
  explicit Texture(SDL_Texture *src);
  explicit Texture(SDL_Texture *src, int x, int y, int w, int h);
  ~Texture();
  int h_ = 0;
  int w_ = 0;
  double scale_h_ = 1, scale_w_ = 1;
  int center_x_ = 0, center_y_ = 0;
  void Render(SDL_Renderer* renderer, int x, int y) const;
 private:
  SDL_Rect *src_rect_;
  SDL_Texture *texture_;
};

#endif//TETRIS_TEXTURE_H_
