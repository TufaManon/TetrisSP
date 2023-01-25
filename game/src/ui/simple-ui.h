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
// Created by Tufa Manon on 2023/1/20.
//
#include <vector>
#include "ui.h"
#ifndef TETRISSP_GAME_SRC_UI_SIMPLE_UI_H_
#define TETRISSP_GAME_SRC_UI_SIMPLE_UI_H_
namespace tetris_sp::game::ui {
class SimpleUI : public UI {
 public:
  void SetRequestSender(const RequestSender &sender) override;
  void ResetStatus() override;
  ~SimpleUI() override;
  void Render() const override;
  void HandleInput(SDL_Event &event) override;
  void Update(uint64_t delay) override;
 protected:
  RequestSender sender_;
  std::vector<Widget *> widgets_;
  response::Response *SendRequest(const request::Request &request);
};

} // tetris_sp::game::ui

#endif //TETRISSP_GAME_SRC_UI_SIMPLE_UI_H_
