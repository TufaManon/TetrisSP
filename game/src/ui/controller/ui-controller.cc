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
// Created by TUfa Manon on 2023/1/19.
//

#include "ui-controller.h"

#include "resource-manager.h"

namespace tetris_sp::game::ui::controller {
void UIController::SetTarget(UI *ui) { ui_ = ui; }
void UIController::HandleInput(SDL_Event &event) { ui_->HandleInput(event); }
UIController::UIController() : ui_(nullptr) {
  index_ui_.SetRequestSender(
      [](request::Request request_1) -> response::Response {
        return {};
      });
  SetTarget(&index_ui_);
}
void UIController::Render() {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  ui_->Render();
  SDL_RenderPresent(renderer);
}
}  // namespace tetris_sp