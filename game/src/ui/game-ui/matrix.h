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
// Created by TufaManon on 2023/1/19.
//

#ifndef TETRISSP_GAME_SRC_UI_GAME_UI_MATRIX_H_
#define TETRISSP_GAME_SRC_UI_GAME_UI_MATRIX_H_
#include <vector>
#include <array>
#include <SDL.h>
#include "ui/widget.h"
#include "sdl/texture.h"
#include "tetrimino/mino.h"
#include "response/response.h"
namespace tetris_sp::game::game_ui {

class Matrix : public ui::Widget {
 public:
  explicit Matrix(int cell_size);
  ~Matrix() override;
  void Render() const override;
  void HandleInput(SDL_Event &event) override;
  void Update(uint64_t delay) override;
  void AddTrack(tetrimino::Color color, int x);
  void DestroyLineEffect(int line_num, const std::array<tetrimino::Color, 10> &colors);
  response::MatrixRenderResponse matrix_render_response_{};
  int x_, y_;
 private:
  void DrawMino() const;
  void InitMinoTextures();
  void InitFrame();
  SDL_Texture *back_img_;
  sdl::Texture *minos_[7];
  sdl::Texture *frame_;
  int cell_size_;
};
} // game_ui

#endif //TETRISSP_GAME_SRC_UI_GAME_UI_MATRIX_H_