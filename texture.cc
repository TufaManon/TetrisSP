//
// Created by Tufa Manon on 2023/1/27.
//

#include "texture.h"
Texture::Texture(SDL_Texture *src) : src_rect_(nullptr), texture_(src) {
}
void Texture::Render(SDL_Renderer *renderer, int x, int y) const {
  SDL_Rect rect{static_cast<int>(x - (center_x_ * scale_w_)), static_cast<int>(y - (center_y_ * scale_h_)),
                static_cast<int>(w_ * scale_w_), static_cast<int>(h_ * scale_h_)};
  SDL_RenderCopy(renderer, texture_, src_rect_, &rect);
}
Texture::~Texture() {
  delete src_rect_;
}
Texture::Texture(SDL_Texture *src, int x, int y, int w, int h) : texture_(src), src_rect_(new SDL_Rect{x, y, w, h}) {
}
