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

#include "standard-game-ui.h"
#include "matrix.h"

namespace tetris_sp::game::game_ui {
StandardGameUI::StandardGameUI() {
  auto *matrix = new Matrix(32);
  matrix_ = matrix;
  widgets_.push_back(matrix);
}
void StandardGameUI::HandleInput(SDL_Event &event) {
  SimpleUI::HandleInput(event);
}
void StandardGameUI::Render() const {
  SimpleUI::Render();
}
void StandardGameUI::Update(uint64_t delay) {
  SimpleUI::Update(delay);
  request::Request req{};
  req.type = MATRIX_RENDER_REQUEST;
  if (sender_) {
    response::Response *resp = sender_(req);
    if (matrix_ != nullptr && resp != nullptr)
      matrix_->matrix_render_response_ = resp->matrix_render_response;
  }
}
} // game_ui