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

#ifndef TETRISSP_GAME_SRC_RESOURCE_MANAGER_H_
#define TETRISSP_GAME_SRC_RESOURCE_MANAGER_H_
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

namespace tetris_sp::game {

class ResourceManager {
 private:
  static std::map<std::string, SDL_Texture *> sdl_texture_store_;
  static std::map<std::string, TTF_Font *> sdl_font_store_;
 public:
  static SDL_Window *window_;
  static SDL_Renderer *renderer_;

  static SDL_Texture *GetTexture(const std::string &path);
  static TTF_Font *GetFont(const std::string &path);
  static void Init();
  static void Close();
};

} // game

#endif //TETRISSP_GAME_SRC_RESOURCE_MANAGER_H_
