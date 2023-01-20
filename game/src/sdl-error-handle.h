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

#ifndef TETRISSP_GAME_SRC_SDL_ERROR_HANDLE_H_
#define TETRISSP_GAME_SRC_SDL_ERROR_HANDLE_H_
#include <ctime>
#include <SDL.h>
namespace tetris_sp::game::sdl_error_handle {
void LogErrorAndAbort(const char *message) {
  tm s_time{};
  time_t t = time(nullptr);
  localtime_s(&s_time, &t);
  char tmp[32] = {0};
  strftime(tmp, sizeof tmp, "%Y-%m-%d_%H:%M:%S", &s_time);
  SDL_Log("{%s} %s, the sdl error message: %s", tmp, message, SDL_GetError());
  abort();
}
}

#endif //TETRISSP_GAME_SRC_SDL_ERROR_HANDLE_H_
