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

#include <SDL.h>
#include "matrix.h"
#include "resource-manager.h"
#include "sdl-error-handle.h"
namespace tetris_sp::game::game_ui {

void Matrix::Render() {

}
void Matrix::HandleInput(SDL_Event &event) {

}
Matrix::~Matrix() {
  SDL_DestroyTexture(back_board_);
}
Matrix::Matrix(int cell_size) : back_board_(nullptr), cell_size_(cell_size) {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  back_board_ = SDL_CreateTexture(renderer,
                                  SDL_PixelFormatEnum::SDL_PIXELFORMAT_ARGB8888,
                                  SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,
                                  cell_size * 10,
                                  cell_size * 20);
  if (back_board_ == nullptr) sdl_error_handle::LogErrorAndAbort("create texture failed");
}
} // game_ui