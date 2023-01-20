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

#include "index-ui.h"
#include "selection-bar.h"
#include "resource-manager.h"

namespace tetris_sp::game::ui::index_ui {
void IndexUI::HandleInput(SDL_Event &event) {
  for (const auto &widget : widgets_) {
    widget->HandleInput(event);
  }
}
void IndexUI::ResetStatus() {

}
IndexUI::IndexUI() {
  constexpr SDL_Rect sdl_rect{600, 300, 400, 300};
  auto *solo_bar = new SelectionBar("solo", sdl_rect);
  solo_bar->OnClick([]() -> void {
    SDL_Log("click solo");
  });
  widgets_.push_back(solo_bar);
}
IndexUI::~IndexUI() {
  for (const auto &item : widgets_) {
    delete item;
  }
}
} // index_ui