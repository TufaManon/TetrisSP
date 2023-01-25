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
// Created by Tufa Manon on 2023/1/23.
//

#include "point.h"
namespace tetris_sp::game::utils {

bool Point::operator==(const Point &rhs) const {
  return x == rhs.x &&
      y == rhs.y;
}
bool Point::operator!=(const Point &rhs) const {
  return !(rhs == *this);
}
bool Point::operator<(const Point &rhs) const {
  if (x < rhs.x)
    return true;
  if (rhs.x < x)
    return false;
  return y < rhs.y;
}
bool Point::operator>(const Point &rhs) const {
  return rhs < *this;
}
bool Point::operator<=(const Point &rhs) const {
  return !(rhs < *this);
}
bool Point::operator>=(const Point &rhs) const {
  return !(*this < rhs);
}
Point::Point(int x, int y) {
  this->x = x;
  this->y = y;
}
std::ostream &operator<<(std::ostream &os, const Point &point) {
  os << "x: " << point.x << " y: " << point.y;
  return os;
}
Point Point::operator-(const Point &rhs) const {
  return {x - rhs.x, y - rhs.y};
}
const Point &Point::operator-=(const Point &rhs) {
  this->x -= rhs.x;
  this->y -= rhs.y;
  return *this;
}
Point Point::operator+(const Point &rhs) const {
  return {x + rhs.x, y + rhs.y};
}
const Point &Point::operator+=(const Point &rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}
}
