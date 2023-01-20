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
// Created by wwwfl on 2023/1/19.
//

#ifndef TETRISSP_GAME_SRC_COLOR_ARGB_H_
#define TETRISSP_GAME_SRC_COLOR_ARGB_H_

#include <cstdint>
#include <string>
#include <minmax.h>
#include <SDL.h>

namespace tetris_sp::game::color {

class ARGB {
 public:
  uint8_t red_, greed_, blue_, alpha_;
  explicit ARGB();
  explicit ARGB(std::string hex_str, uint8_t alpha = 255);
  SDL_Color SDLFul();
 private:
  static double ToPercentage(uint8_t ui8);
};

} // color

#endif //TETRISSP_GAME_SRC_COLOR_ARGB_H_
