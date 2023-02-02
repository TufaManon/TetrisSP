//
// Created by Tufa Manon on 2023/1/27.
//

#ifndef TETRIS_TTY_H_
#define TETRIS_TTY_H_
#include <SDL.h>

struct Vec2 {
  int x, y;
  Vec2(int x_, int y_) : x(x_), y(y_){};
  Vec2() : x(0), y(0) {}
  bool operator<(const Vec2 &rhs) const {
    return x * x + y * y < rhs.x * rhs.x + rhs.y * rhs.y;
  }
  bool operator>(const Vec2 &rhs) const {
    return rhs < *this;
  }
  bool operator<=(const Vec2 &rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const Vec2 &rhs) const {
    return !(*this < rhs);
  }
  bool operator==(const Vec2 &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  bool operator!=(const Vec2 &rhs) const {
    return !(rhs == *this);
  }
  Vec2 operator+(const Vec2 &rhs) const {
    return {x + rhs.x, y + rhs.y};
  }
  Vec2 operator-(const Vec2 &rhs) const {
    return {x - rhs.x, y - rhs.y};
  }
};

#endif//TETRIS_TTY_H_
