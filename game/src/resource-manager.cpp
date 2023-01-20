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

#include "resource-manager.h"

#include "sdl-error-handle.h"

namespace tetris_sp::game {
SDL_Renderer *ResourceManager::renderer_ = nullptr;
SDL_Window *ResourceManager::window_ = nullptr;
std::map<std::string, SDL_Texture *> ResourceManager::sdl_texture_store_;
std::map<std::string, TTF_Font *> ResourceManager::sdl_font_store_;

SDL_Texture *ResourceManager::GetTexture(const std::string &path) {
  if (sdl_texture_store_.find(path) == sdl_texture_store_.end()) {
    SDL_Texture *texture = IMG_LoadTexture(renderer_, path.c_str());
    if (texture == nullptr) {
      sdl_error_handle::LogErrorAndAbort("load img source failed");
    }
    sdl_texture_store_[path] = texture;
    return texture;
  } else
    return sdl_texture_store_[path];
}
TTF_Font *ResourceManager::GetFont(const std::string &path) {
  if (sdl_font_store_.find(path) == sdl_font_store_.end()) {
    TTF_Font *font = TTF_OpenFont(("assets/" + path).c_str(), 64);
    if (font == nullptr) {
      sdl_error_handle::LogErrorAndAbort("load font failed");
    }
    sdl_font_store_[path] = font;
    return font;
  }
  return sdl_font_store_[path];
}
void ResourceManager::Init() {
  const Uint32 kSdlInitFlag =
      SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO;
  const Uint32 kImgInitFlag = IMG_INIT_PNG | IMG_INIT_JPG;
  const Uint32 kMixInitFlag = MIX_INIT_MP3 | MIX_INIT_FLAC;

  int init = SDL_Init(kSdlInitFlag);
  if (init != 0) {
    sdl_error_handle::LogErrorAndAbort("init sdl failed");
  }
  window_ =
      SDL_CreateWindow("tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       1600, 900, SDL_WINDOW_SHOWN);
  if (window_ == nullptr) {
    sdl_error_handle::LogErrorAndAbort("create window failed");
  }
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (renderer_ == nullptr) {
    sdl_error_handle::LogErrorAndAbort("create renderer failed");
  }
  int img_init = IMG_Init(kImgInitFlag);
  if (img_init != kImgInitFlag) {
    sdl_error_handle::LogErrorAndAbort("init img failed");
  }
  int ttf_init = TTF_Init();
  if (ttf_init != 0) {
    sdl_error_handle::LogErrorAndAbort("init ttf failed");
  }

  int mix_init = Mix_Init(kMixInitFlag);
  if (mix_init != kMixInitFlag) {
    sdl_error_handle::LogErrorAndAbort("init mix failed");
  }
}
void ResourceManager::Close() {
  for (const auto &item : sdl_font_store_) {
    TTF_CloseFont(item.second);
  }
  for (const auto &item : sdl_texture_store_) {
    SDL_DestroyTexture(item.second);
  }
  SDL_DestroyRenderer(renderer_);

  SDL_DestroyWindow(window_);

  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}
}  // namespace tetris_sp