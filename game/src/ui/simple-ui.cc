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

#include "simple-ui.h"
namespace tetris_sp::game::ui {

void SimpleUI::SetRequestSender(const UI::RequestSender &sender) {
  sender_ = sender;
}
void SimpleUI::ResetStatus() {
  //sender_ = nullptr;
}
void SimpleUI::Render() const {
  for (const auto &item : widgets_) {
    item->Render();
  }
}
void SimpleUI::HandleInput(SDL_Event &event) {
  for (const auto &item : widgets_) {
    item->HandleInput(event);
  }
}
response::Response *SimpleUI::SendRequest(const request::Request &request) {
  if (sender_ == nullptr) return nullptr;
  else return sender_(request);
}
SimpleUI::~SimpleUI() {
  for (const auto &item : widgets_) {
    delete item;
  }
}
void SimpleUI::Update(uint64_t delay) {

}
} // tetris_sp::game::ui
