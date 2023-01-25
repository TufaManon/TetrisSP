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

#ifndef TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_H_
#define TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_H_
#include <cinttypes>
#include <SDL.h>
#include "request/request.h"
#include "response/response.h"
#include "server.h"
#include "tetris-engine.h"
#include "tetrimino/seven-bag-generator.h"

namespace tetris_sp::game::server {

class SingleGameService : public Server {
 public:
  void Update(uint64_t delay) override;
  void HandleInput(SDL_Event &event) override;
  response::Response HandleRequest(const request::Request &req) override;
 private:
  TetrisEngine engine_{new tetrimino::SevenBagGenerator()};
  bool left_button_down = false;
  bool right_button_down = false;
  bool soft_down_button_down = false;
  bool hard_down_button_down = false;
  bool l_rotate_button_down = false;
  bool r_rotate_button_down = false;
  bool hold_button_down = false;
  uint64_t das = 167;
  uint64_t arr = 33;
  uint64_t timer = 0;
  bool is_das = true;
  bool arr_right = true;
};

} // server

#endif //TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_H_
