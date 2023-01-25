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
// Created by Tufa Manon on 2023/1/22.
//

#include <random>
#include <SDL.h>
#include "seven-bag-generator.h"

namespace tetris_sp::game::tetrimino {
SevenBagGenerator::SevenBagGenerator() : top(0), types_{I, J, L, O, S, T, Z} {
  Shuffle();
}
void SevenBagGenerator::Shuffle() {
  std::default_random_engine random_engine(SDL_GetTicks());
  for (int i = 0; i < 6; ++i) {
    std::uniform_int_distribution<int> int_distribution(0, 6 - i - 1);
    int random_index = int_distribution(random_engine) + i + 1;
    std::swap(types_[i], types_[random_index]);
  }
}
Type SevenBagGenerator::GetType() {
  if (top == 7) {
    Shuffle();
    top = 0;
  }
  return types_[top++];
}
} // tetrimino