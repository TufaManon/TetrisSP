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

#ifndef TETRISSP_GAME_SRC_UI_INDEX_UI_SELECTION_BAR_H_
#define TETRISSP_GAME_SRC_UI_INDEX_UI_SELECTION_BAR_H_

#include "ui/widget.h"
#include <functional>
#include <string>
#include <SDL.h>

namespace tetris_sp {
namespace game {
namespace ui {
namespace index_ui {

class SelectionBar : public Widget {
 public:
  SDL_Rect rect_;
  explicit SelectionBar(const char *txt, const SDL_Rect rect);
  ~SelectionBar() override;
  void Render() override;
  void HandleInput(SDL_Event &event) override;
  virtual void OnClick(const std::function<void(void)> &callback);
 private:
  SDL_Texture *font_texture_;
  std::function<void(void)> callback_;
  std::string txt_;
};

} // tetris_sp
} // game
} // ui
} // index_ui

#endif //TETRISSP_GAME_SRC_UI_INDEX_UI_SELECTION_BAR_H_
