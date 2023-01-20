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
// Created by TUfa Manon. on 2023/1/19.
//

#ifndef TETRIS_SP_SRC_GAME_UI_WIDGET_H_
#define TETRIS_SP_SRC_GAME_UI_WIDGET_H_
#include <SDL.h>

namespace tetris_sp::game::ui {

class Widget {

 public:
  virtual ~Widget() = default;
  virtual void Render() = 0;
  virtual void HandleInput(SDL_Event &event) = 0;
};

} // ui

#endif //TETRIS_SP_SRC_GAME_UI_WIDGET_H_
