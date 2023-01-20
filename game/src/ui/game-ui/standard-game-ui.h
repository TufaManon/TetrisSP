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

#ifndef TETRISSP_GAME_SRC_UI_GAME_UI_STANDARD_GAME_UI_H_
#define TETRISSP_GAME_SRC_UI_GAME_UI_STANDARD_GAME_UI_H_
#include "ui/ui.h"
namespace tetris_sp::game::game_ui {

class StandardGameUI : public ui::UI {
 public:
  ~StandardGameUI() override = default;
  void HandleInput(SDL_Event &event) override;
  void ResetStatus() override;
};

} // game_ui

#endif //TETRISSP_GAME_SRC_UI_GAME_UI_STANDARD_GAME_UI_H_
