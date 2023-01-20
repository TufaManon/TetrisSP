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
#include <stdint.h>

namespace tetris_sp {
namespace game {
namespace response {

struct UISwitchResponse {
  uint32_t type;
  uint64_t timestamp;
  uint32_t ui_id;
};

union Response {
  unsigned int type;
  UISwitchResponse ui_switch_response;
};

enum ResponseType {
  UI_SWITCH_RESPONSE,
};
} // tetris_sp
} // game
} // response

#endif //_RESPONSE_H_
