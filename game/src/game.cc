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
#include "ui/widget.h"
#include "ui/controller/ui-controller.h"

namespace tetris_sp::game {
uint64_t Game::current_time_ = 0;

void Game::Begin() {
  ResourceManager::Init();
  ui::Widget *widget = new ui::controller::UIController();
  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) == 1) {
      if (event.type == SDL_QUIT) quit = true;
      else widget->HandleInput(event);
    }
    const uint64_t time = SDL_GetTicks64();
    const uint64_t delay = time - current_time_;
    current_time_ = time;
    widget->Update(delay);
    widget->Render();
  }
  delete widget;
  ResourceManager::Close();
}
} // namespace tetris_sp
