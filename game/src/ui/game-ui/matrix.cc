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
#include <random>
#include <SDL.h>
#include <yaml-cpp/yaml.h>
#include "matrix.h"
#include "resource-manager.h"
namespace tetris_sp::game::game_ui {
namespace {
std::map<tetrimino::Type, tetrimino::Color> kColorTypeMap = {
    {tetrimino::O, tetrimino::YELLOW},
    {tetrimino::I, tetrimino::LIGHT_BLUE},
    {tetrimino::T, tetrimino::VIOLET},
    {tetrimino::L, tetrimino::ORANGE},
    {tetrimino::J, tetrimino::BLUE},
    {tetrimino::S, tetrimino::GREEN},
    {tetrimino::Z, tetrimino::RED}
};
}
void Matrix::Render() const {
  SDL_Renderer *renderer = ResourceManager::renderer_;
  // draw background image
  SDL_RenderCopy(renderer, back_img_, nullptr, nullptr);
  frame_->CopyTo(nullptr);
  // draw minos
  DrawMino();
}
void Matrix::HandleInput(SDL_Event &event) {

}
Matrix::~Matrix() = default;
Matrix::Matrix(int cell_size)
    : cell_size_(cell_size),
      x_(0),
      y_(0),
      frame_(),
      back_img_(),
      minos_{nullptr} {
  back_img_ = ResourceManager::GetTexture("assets/backg.jpg");
  x_ = 1600 / 2 - cell_size * 10 / 2;
  y_ = 900 / 2 - cell_size * 20 / 2;
  InitFrame();
  InitMinoTextures();

  std::default_random_engine random_engine(SDL_GetTicks());
  std::uniform_int_distribution<int> int_distribution(0, 6);
}
void Matrix::Update(uint64_t delay) {
}
void Matrix::DrawMino() const {
  if (matrix_render_response_.lock_map_ != nullptr) {
    for (int i = 2; i < 22; ++i)
      for (int j = 0; j < 10; ++j)
        if (matrix_render_response_.lock_map_[i][j] != nullptr) {
          tetrimino::Color color = matrix_render_response_.lock_map_[i][j]->color;
          SDL_Rect rect{frame_->x_ + j * cell_size_, frame_->y_ + (i - 2) * cell_size_, cell_size_, cell_size_};
          minos_[color]->CopyTo(&rect, nullptr);
        }
  }
  if (matrix_render_response_.activity_tetrimino_ != nullptr) {
    for (const auto &item : matrix_render_response_.activity_tetrimino_->mino_relative_position) {
      SDL_Rect rect{frame_->x_ + (matrix_render_response_.activity_tetrimino_->pos.x + item.x) * cell_size_,
                    frame_->y_ + (matrix_render_response_.activity_tetrimino_->pos.y + item.y - 2) * cell_size_,
                    cell_size_, cell_size_};
      minos_[kColorTypeMap[matrix_render_response_.activity_tetrimino_->type]]->CopyTo(&rect, nullptr);
    }
  }
}
void Matrix::InitMinoTextures() {
  YAML::Node info = YAML::LoadFile("assets/tetrio-info.yaml");
  SDL_Texture *mino_sequence = ResourceManager::GetTexture("assets/tetrio.png");
  //TODO check info

  int size = info["size"].as<int>();
  int w = info["w"].as<int>();
  auto color_map = info["color-map"].as<YAML::Node>();
  SDL_Rect rect{0, 0, size, size};
  auto color_names = {"red", "orange", "yellow", "green", "light-blue", "blue", "violet"};
  int color_index = 0;
  for (const auto &item : color_names) {
    int i = color_map[item].as<int>();
    rect.y = (i / w) * size;
    rect.x = (i % w) * size;
    minos_[color_index] = new sdl::Texture(mino_sequence, rect);
    color_index++;
  }
}
void Matrix::InitFrame() {
  YAML::Node info = YAML::LoadFile("assets/frame-info.yaml");
  if (info.IsNull()) SDL_Log("Can't load the frame info yaml file");
  SDL_Texture *texture = ResourceManager::GetTexture("assets/frame.png");
  frame_ = new sdl::Texture(texture);
  frame_->h_ = info["h"].as<int>();
  frame_->w_ = info["w"].as<int>();
  double scale = cell_size_ / info["cell-size"].as<double>();
  frame_->center_x_ = info["matrix-x"].as<int>();
  frame_->center_y = info["matrix-y"].as<int>();
  frame_->x_ = x_;
  frame_->y_ = y_;
  frame_->scale_h_ = frame_->scale_w_ = scale;
}
void Matrix::AddTrack(tetrimino::Color color, int x) {

}
void Matrix::DestroyLineEffect(int line_num, const std::array<tetrimino::Color, 10> &colors) {

}
} // game_ui1