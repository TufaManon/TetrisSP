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

#include "selection-bar.h"

#include "color/argb.h"
#include "resource-manager.h"
namespace tetris_sp {
namespace game {
namespace ui {
namespace index_ui {
void SelectionBar::Render() {
  int w, h = 0;
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_QueryTexture(font_texture_, nullptr, nullptr, &w, &h);
  SDL_SetRenderTarget(renderer, nullptr);
  const int margin_w = rect_.w / 2 - w / 2;
  const int margin_h = rect_.h / 2 - h / 2;
  const SDL_Rect font_rect{rect_.x + margin_w, rect_.y + margin_h, w, h};
  SDL_RenderCopy(renderer, font_texture_, nullptr, &font_rect);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawRect(renderer, &rect_);
}
void SelectionBar::OnClick(const std::function<void(void)> &callback) {
  callback_ = callback;
}
SelectionBar::SelectionBar(const char *txt, const SDL_Rect rect)
    : rect_(rect), txt_(txt) {
  TTF_Font *font = ResourceManager::GetFont("mini_pixel-7.ttf");
  SDL_Renderer *renderer = ResourceManager::renderer_;
  SDL_Surface *utf_8_blended =
      TTF_RenderUTF8_Blended(font, txt, color::ARGB("#fff").SDLFul());
  font_texture_ = SDL_CreateTextureFromSurface(renderer, utf_8_blended);
  SDL_FreeSurface(utf_8_blended);
}
void SelectionBar::HandleInput(SDL_Event &event) {
  if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
    const SDL_Point point{event.button.x, event.button.y};
    if (SDL_PointInRect(&point, &rect_)) {
      callback_();
    }
  }
}
SelectionBar::~SelectionBar() { SDL_DestroyTexture(font_texture_); }
}  // namespace index_ui
}  // namespace ui
}  // namespace game
}  // namespace tetris_sp