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
// Created by Tufa Manon on 2023/1/22.
//

#include "single-game-service.h"

namespace tetris_sp::game::server {
void SingleGameService::Update(uint64_t delay) {
  engine_.Update();
  if (right_button_down || left_button_down) {
    timer += delay;
    if (is_das && timer > das) {
      is_das = false;
      timer = 0;
    } else if (!is_das && timer > arr) {
      engine_.Move(arr_right);
      timer = 0;
    }
  } else
    is_das = true;
}
void SingleGameService::HandleInput(SDL_Event &event) {
  if (event.type == SDL_EventType::SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_A:if (left_button_down) break;
        left_button_down = true;
        engine_.Move(false);
        arr_right = false;
        break;
      case SDL_SCANCODE_S:if (soft_down_button_down) break;
        soft_down_button_down = true;
        engine_.configurable_.falling_interval /= 20;
        break;
      case SDL_SCANCODE_D:if (right_button_down) break;
        right_button_down = true;
        engine_.Move(true);
        arr_right = true;
        break;
      case SDL_SCANCODE_W:if (hard_down_button_down) break;
        hard_down_button_down = true;
        engine_.HardDrop();
        break;
      case SDL_SCANCODE_J:if (l_rotate_button_down) break;
        l_rotate_button_down = true;
        engine_.Rotate(false);
        break;
      case SDL_SCANCODE_K:if (r_rotate_button_down) break;
        r_rotate_button_down = true;
        engine_.Rotate(true);
        break;
      case SDL_SCANCODE_L:if (hold_button_down) break;
        hold_button_down = true;
        engine_.Hold();
        break;
      default:break;
    }
  } else if (event.type == SDL_EventType::SDL_KEYUP) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_A:left_button_down = false;
        arr_right = true;
        break;
      case SDL_SCANCODE_S:soft_down_button_down = false;
        engine_.configurable_.falling_interval *= 20;
        break;
      case SDL_SCANCODE_D:right_button_down = false;
        arr_right = false;
        break;
      case SDL_SCANCODE_W:hard_down_button_down = false;
        break;
      case SDL_SCANCODE_J:l_rotate_button_down = false;
        break;
      case SDL_SCANCODE_K:r_rotate_button_down = false;
        break;
      case SDL_SCANCODE_L:hold_button_down = false;
        break;
      default:break;
    }
  }
}
response::Response SingleGameService::HandleRequest(const request::Request &req) {
  if (req.type == MATRIX_RENDER_REQUEST) {
    return engine_.GeyMatrixRenderResponse();
  } else return {};
}
} // server