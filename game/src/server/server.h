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

#ifndef TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_CC_SERVER_H_
#define TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_CC_SERVER_H_

#include <response/response.h>
#include <request/request.h>
#include <SDL.h>
#include <cinttypes>
namespace tetris_sp::game::server {

class Server {
 public:
  virtual void Update(uint64_t delay) = 0;
  virtual void HandleInput(SDL_Event &event) = 0;
  virtual response::Response HandleRequest(const request::Request &req) = 0;
};

} // server

#endif //TETRISSP_GAME_SRC_SERVER_SINGLE_GAME_SERVICE_CC_SERVER_H_
