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

#ifndef TETRISSP_GAME_SRC_SDL_TEXTURE_H_
#define TETRISSP_GAME_SRC_SDL_TEXTURE_H_
#include <SDL.h>
namespace tetris_sp::game::sdl {

class Texture {
 public:
  explicit Texture(SDL_Texture *src);
  explicit Texture(SDL_Texture *src, const SDL_Rect &rect);
  void CopyTo(SDL_Rect *d_rect, SDL_Texture *target);
  void CopyTo(SDL_Texture *target);
  void SetRect(const SDL_Rect &rect);
  int h_, w_;
  int x_, y_;
  double scale_h_, scale_w_;
  int center_x_, center_y;
 private:
  SDL_Texture *src_;
  SDL_Rect rect_;
  bool set_rect_;
};

} // sdl

#endif //TETRISSP_GAME_SRC_SDL_TEXTURE_H_
