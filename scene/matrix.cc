//
// Created by Tufa Manon on 2023/1/27.
//

#include "matrix.h"
const int Tetrimino::kMino_pos_pool_[7][8] = {
    {-1, 0, 0, 0, 1, 0, 2, 0},
    {-1, -1, -1, 0, 0, 0, 1, 0},
    {-1, 0, 0, 0, 1, 0, 1, -1},
    {0, -1, 0, 0, 1, -1, 1, 0},
    {-1, 0, 0, 0, 0, -1, 1, -1},
    {-1, 0, 0, -1, 0, 0, 1, 0},
    {-1, -1, 0, -1, 0, 0, 1, 0}};
Tetrimino::Tetrimino(TetriminoType type) : pos_(4, 1), mino_point_counter_(4), type_(type), ori_(NORTH) {
  int pol_index = 0;
  switch (type) {
    case O: pol_index = 3; break;
    case I: pol_index = 0; break;
    case T: pol_index = 5; break;
    case L: pol_index = 2; break;
    case J: pol_index = 1; break;
    case S: pol_index = 4; break;
    case Z: pol_index = 6; break;
  }
  for (int i = 0; i < 4; ++i) {
    mino_relative_pos_[i].x = kMino_pos_pool_[pol_index][i * 2];
    mino_relative_pos_[i].y = kMino_pos_pool_[pol_index][i * 2 + 1];
  }
}
Matrix::Matrix() : active_(nullptr), next_(), held_(), phase_(0) {
  ghost_ = new Tetrimino(T);
  for (int i = 0; i < 22; ++i) {
    data_.push_back(new Row{nullptr});
  }
}
Matrix::~Matrix() {
  for (const auto &row : data_) {
    for (const auto &mino : *row) {
      mino->mino_point_counter_--;
      if (mino->mino_point_counter_ <= 0) {
        delete mino;
      }
    }
  }
  data_.clear();
  delete ghost_;
}
void Matrix::DeleteRow(int row_index) {
  auto it = data_.begin();
  std::advance(it, row_index);
  for (const auto &mino : **it) {
    if (mino != nullptr) {
      mino->mino_point_counter_--;
      if (mino->mino_point_counter_ <= 0) delete mino;
    }
  }
  delete *it;
  data_.erase(it);
  data_.push_front(new Row{nullptr});
}
bool Matrix::IsLandsOnTheSurface(Tetrimino &tetrimino) {
  auto it = data_.begin();
  std::advance(it, tetrimino.pos_.y);
  for (const auto &v2 : tetrimino.mino_relative_pos_) {
    if (tetrimino.pos_.y + v2.y >= 21 || tetrimino.pos_.y + v2.y < 0) return true;
    std::advance(it, v2.y + 1);
    if ((*it)->at(v2.x + tetrimino.pos_.x) != nullptr) return true;
    std::advance(it, -v2.y - 1);
  }
  return false;
}
bool Matrix::IsEmbedsInObs(Tetrimino &tetrimino) {
  auto it = data_.begin();
  std::advance(it, tetrimino.pos_.y);
  for (const auto &v2 : tetrimino.mino_relative_pos_) {
    if (tetrimino.pos_.y + v2.y > 21 || tetrimino.pos_.y + v2.y < 0) return true;
    if (tetrimino.pos_.x + v2.x > 9 || tetrimino.pos_.x + v2.x < 0) return true;
    std::advance(it, v2.y);
    if ((*it)->at(v2.x + tetrimino.pos_.x) != nullptr) return true;
    std::advance(it, -v2.y);
  }
  return false;
}
void Matrix::Solidify() {
  auto it = data_.begin();
  std::advance(it, active_->pos_.y);
  for (const auto &v2 : active_->mino_relative_pos_) {
    std::advance(it, v2.y);
    (*it)->at(v2.x + active_->pos_.x) = active_;
    std::advance(it, -v2.y);
  }
}
int Matrix::CheckTSpin() {
  if (active_->type_ == T) {
    Vec2 a = {-1, -1}, b = {1, -1}, c = {1, 1}, d = {-1, 1};
    std::array<Vec2, 4> points = {a, b, c, d};
    std::array<bool, 4> points_state = {false, false, false, false};
    auto it = data_.begin();
    std::advance(it, active_->pos_.y);
    int counter = 0;
    for (const auto &v2 : points) {
      if (v2.y + active_->pos_.y >= 0 && v2.y + active_->pos_.y < 22) {
        if (v2.x + active_->pos_.x >= 0 && v2.x + active_->pos_.x < 10) {
          std::advance(it, v2.y);
          if ((*it)->at(v2.x + active_->pos_.x) != nullptr) {
            points_state[counter] = true;
          }
          counter++;
          std::advance(it, -v2.y);
        }
      }
    }
    int points_state_counter = 0;
    for (const auto &item : points_state) {
      if (item) points_state_counter++;
    }
    if (points_state_counter >= 3) {
      if (active_->ori_ == NORTH && points_state[0] && points_state[1]) return 2;
      if (active_->ori_ == SOUTH && points_state[2] && points_state[3]) return 2;
      if (active_->ori_ == EAST && points_state[1] && points_state[2]) return 2;
      if (active_->ori_ == WEST && points_state[0] && points_state[3]) return 2;
      return 3;
    }
  }
  return 0;
}
