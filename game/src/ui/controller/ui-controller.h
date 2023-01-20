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
// Created by TufaManon on 2023/1/19.
//

#ifndef TETRISSP_GAME_SRC_UI_CONTROLLER_UI_CONTROLLER_H_
#define TETRISSP_GAME_SRC_UI_CONTROLLER_UI_CONTROLLER_H_
#include "ui/ui.h"
#include "ui/index-ui/index-ui.h"

namespace tetris_sp::game::ui::controller {

class UIController {
 public:
  explicit UIController();
  virtual ~UIController() = default;
  void SetTarget(UI *ui);
  virtual void HandleInput(SDL_Event &event);
  virtual void Render();
 private:
  UI *ui_;
  index_ui::IndexUI index_ui_;
};

} // controller

#endif //TETRISSP_GAME_SRC_UI_CONTROLLER_UI_CONTROLLER_H_
