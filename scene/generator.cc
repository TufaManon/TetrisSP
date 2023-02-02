//
// Created by Tufa Manon on 2023/1/29.
//

#include "generator.h"
#include <random>
Generator::Generator() : top(0), types_{I, J, L, O, S, T, Z} {
  Shuffle();
}
void Generator::Shuffle() {
  std::default_random_engine random_engine(SDL_GetTicks());
  for (int i = 0; i < 6; ++i) {
    std::uniform_int_distribution<int> int_distribution(0, 6 - i - 1);
    int random_index = int_distribution(random_engine) + i + 1;
    std::swap(types_[i], types_[random_index]);
  }
}
TetriminoType Generator::GetType() {
  if (top == 7) {
    Shuffle();
    top = 0;
  }
  return types_[top++];
}