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
// Created by Maynard Gray on 2023/1/18.
//

#include "game.h"

#include <SDL.h>

#include "resource-manager.h"
#include "ui/controller/ui-controller.h"

namespace tetris_sp {
namespace game {

void Game::Init() { ResourceManager::Init(); }
void Game::Run() {
  bool quit_flag = false;
  ui::controller::UIController controller;
  SDL_Event event;
  while (!quit_flag) {
    while (SDL_PollEvent(&event) == 1) {
      if (event.type == SDL_QUIT)
        quit_flag = true;
      else
        controller.HandleInput(event);
    }
    controller.Render();
  }
}
}  // namespace game
}  // namespace tetris_sp