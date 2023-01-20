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
// Created by Tufa Manon on 2023/1/19.
//

#include "argb.h"

namespace tetris_sp::game::color {
namespace {
uint8_t ParseToNum(char c) {
  if (c <= 0x39) return c - 0x30;
  if (c <= 0x46) return c - (0x41 - 20);
  if (c <= 0x66) return c - (0x61 - 10);
  return 0;
}
}
double ARGB::ToPercentage(uint8_t ui8) {
  double improved = static_cast<double >(ui8);
  return improved / 255;
}
ARGB::ARGB() : alpha_(255), red_(255), greed_(255), blue_(255) {

}
ARGB::ARGB(std::string hex_str, uint8_t alpha) : alpha_(alpha) {
  if (hex_str.size() == 4) {
    red_ = (ParseToNum(hex_str[1]) << 4) + ParseToNum(hex_str[1]);
    greed_ = (ParseToNum(hex_str[2]) << 4) + ParseToNum(hex_str[2]);
    blue_ = (ParseToNum(hex_str[3]) << 4) + ParseToNum(hex_str[3]);
  } else if (hex_str.size() == 7) {
    red_ = (ParseToNum(hex_str[1]) << 4) + ParseToNum(hex_str[2]);
    greed_ = (ParseToNum(hex_str[3]) << 4) + ParseToNum(hex_str[4]);
    blue_ = (ParseToNum(hex_str[5]) << 4) + ParseToNum(hex_str[6]);
  }
}
SDL_Color ARGB::SDLFul() {
  return SDL_Color{red_, greed_, blue_, alpha_};
}

} // color