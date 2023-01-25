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
#include "ui/index-ui/index-ui.h"
#include "ui/game-ui/standard-game-ui.h"
#include "resource-manager.h"
#include "server/single-game-service.h"

namespace tetris_sp::game::ui::controller {

void UIController::Render() const {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  ui_->Render();
  SDL_RenderPresent(renderer);
}
void UIController::HandleInput(SDL_Event &event) {
  if (ui_ != nullptr)
    ui_->HandleInput(event);
  if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
    if (server_ != nullptr)
      server_->HandleInput(event);
  }
}
UIController::UIController() : ui_(), index_(), solo_(), server_(nullptr) {
  single_game_response = new response::Response();
  index_ = new index_ui::IndexUI();
  solo_ = new game_ui::StandardGameUI();
  index_->SetRequestSender([this](const request::Request &req) -> response::Response * {
    if (req.ui_switch_request.reset) solo_->ResetStatus();
    ui_ = solo_;
    server_ = new server::SingleGameService();
    return nullptr;
  });
  solo_->SetRequestSender([this](const request::Request &req) -> response::Response * {
    *single_game_response = server_->HandleRequest(req);
    return single_game_response;
  });
  ui_ = index_;
}
void UIController::Update(uint64_t delay) {
  if (ui_ != nullptr)
    ui_->Update(delay);
  if (server_ != nullptr)
    server_->Update(delay);
}
UIController::~UIController() {
  delete index_;
  delete solo_;
  delete single_game_response;
}
}  // namespace tetris_sp