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

#ifndef TETRIS_SP_GAME_SRC_REQUEST_REQUEST_H_
#define TETRIS_SP_GAME_SRC_REQUEST_REQUEST_H_
#include <cstdint>

namespace tetris_sp::game::request {

struct UISwitchRequest {
  uint32_t type;
  uint64_t timestamp;
  bool result;
};

union Request {
  uint32_t type;
  UISwitchRequest ui_switch_request;
};

enum RequestType {
  UI_SWITCH_REQUEST,
};

} // response

#endif //TETRIS_SP_GAME_SRC_REQUEST_REQUEST_H_
