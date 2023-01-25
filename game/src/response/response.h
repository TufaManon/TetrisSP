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

#ifndef TETRIS_SP_SRC_GAME_RESPONSE_RESPONSE_H_
#define TETRIS_SP_SRC_GAME_RESPONSE_RESPONSE_H_
#include <cstdint>
#include <list>
#include "utils/point.h"
#include "tetrimino/mino.h"
#include "tetrimino/tetrimino.h"

namespace tetris_sp::game::response {
enum ResponseType {
  UI_SWITCH_RESPONSE,
  MATRIX_RENDER_RESPONSE,
};
struct UISwitchResponse {
  ResponseType type;
  uint64_t timestamp;
  uint32_t ui_id;
};

struct MatrixRenderResponse {
  ResponseType type;
  tetrimino::Mino *(*lock_map_)[10];
  std::list<tetrimino::Tetrimino *> *next_queue_;
  tetrimino::Tetrimino *activity_tetrimino_;
  tetrimino::Tetrimino *held_tetrimino_;
  int ghost_off;
};

union Response {
  ResponseType type;
  UISwitchResponse ui_switch_response;
  MatrixRenderResponse matrix_render_response;
};

} // response

#endif //TETRIS_SP_SRC_GAME_RESPONSE_RESPONSE_H_
