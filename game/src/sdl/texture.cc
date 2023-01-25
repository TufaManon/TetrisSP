//  Copyright [2023] [Tufa Manon]
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

//
// Created by Tufa Manon on 2023/1/21.
//

#include "texture.h"
#include "resource-manager.h"

namespace tetris_sp::game::sdl {
void Texture::CopyTo(SDL_Rect *d_rect, SDL_Texture *target) {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_SetRenderTarget(renderer, target);
  SDL_Rect *s_rect = set_rect_ ? &rect_ : nullptr;
  SDL_RenderCopy(renderer, src_, s_rect, d_rect);
  SDL_SetRenderTarget(renderer, nullptr);
}
Texture::Texture(SDL_Texture *src, const SDL_Rect &rect)
    : src_(src), set_rect_(true), rect_(rect),
      h_(rect.h), w_(rect.w), x_(0), y_(0),
      scale_h_(1.0), scale_w_(1.0),
      center_x_(0), center_y(0) {

}
void Texture::SetRect(const SDL_Rect &rect) {
  set_rect_ = true;
  rect_ = rect;
}
Texture::Texture(SDL_Texture *src)
    : src_(src), set_rect_(false), rect_(),
      w_(0), h_(0), x_(0), y_(0),
      scale_h_(1.0), scale_w_(1.0),
      center_x_(0), center_y(0) {
}
void Texture::CopyTo(SDL_Texture *target) {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_Rect rect{static_cast<int>(x_ - (center_x_ * scale_w_)), static_cast<int>(y_ - (center_y * scale_h_)),
                static_cast<int>(w_ * scale_w_), static_cast<int>(h_ * scale_h_)};
  SDL_Rect *s_rect = set_rect_ ? &rect_ : nullptr;
  SDL_Rect *d_rect = h_ != 0 && w_ != 0 ? &rect : nullptr;
  SDL_RenderCopy(renderer, src_, s_rect, d_rect);
}
} // sdl