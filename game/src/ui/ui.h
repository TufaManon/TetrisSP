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

#ifndef TETRIS_SP_GAME_SRC_UI_UI_H_
#define TETRIS_SP_GAME_SRC_UI_UI_H_
#include <SDL.h>

#include <functional>
#include <vector>

#include "request/request.h"
#include "response/response.h"
#include "widget.h"
namespace tetris_sp::game::ui {
class UI {
 public:
  using RequestSender = std::function<response::Response(request::Request)>;
  virtual ~UI() = default;
  virtual void HandleInput(SDL_Event &event) = 0;
  virtual void Render() {
    for (const auto widget : widgets_) {
      widget->Render();
    }
  }
  void SetRequestSender(const RequestSender &sender) { sender_ = sender; };
  virtual void ResetStatus() = 0;

 protected:
  std::vector<Widget *> widgets_;
  RequestSender sender_;
};

}  // namespace tetris_sp

#endif  //TETRIS_SP_GAME_SRC_UI_UI_H_