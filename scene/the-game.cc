//
// Created by Tufa Manon on 2023/1/27.
//

#include "the-game.h"
#include <iomanip>
#include <sstream>
#include "audio.h"
TheGame::~TheGame() = default;
void TheGame::Update(uint64_t delta) {
  lines->message->SetTxt(std::to_string(actuator_.line_counter));
  std::stringstream ss;
  std::chrono::minutes minutes(1);
  std::chrono::seconds seconds(1);
  auto min = actuator_.playing_time_ / minutes;
  auto s = (actuator_.playing_time_ % minutes) / seconds;
  auto mil = (actuator_.playing_time_ % seconds);
  ss << std::setw(2) << std::setfill('0') << min << ":";
  ss << std::setw(2) << std::setfill('0') << s << ":";
  ss << std::setw(2) << std::setfill('0') << mil.count() / 10;
  std::string str;
  ss >> str;
  time_stamp->message->SetTxt(str);
  Scene::Update(delta);
  actuator_.Request(delta);
  if (right_button_down || left_button_down) {
    timer += delta;
    if (is_das && timer > das) {
      is_das = false;
      timer = 0;
    } else if (!is_das && timer > arr) {
      Move(actuator_, transform_);
      timer = 0;
    }
  } else
    is_das = true;
}
void TheGame::HandleEvent(SDL_Event &event) {
  Scene::HandleEvent(event);
  if (event.type == SDL_EventType::SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_A:
        if (left_button_down) break;
        left_button_down = true;
        transform_ = Vec2(-1, 0);
        Move(actuator_, transform_);
        break;
      case SDL_SCANCODE_S:
        if (soft_down_button_down) break;
        soft_down_button_down = true;
        actuator_.falling_interval /= 20;
        break;
      case SDL_SCANCODE_D:
        if (right_button_down) break;
        right_button_down = true;
        transform_ = Vec2(1, 0);
        Move(actuator_, transform_);
        break;
      case SDL_SCANCODE_W:
        if (hard_down_button_down) break;
        hard_down_button_down = true;
        HardDrop(actuator_);
        break;
      case SDL_SCANCODE_J:
        if (l_rotate_button_down) break;
        l_rotate_button_down = true;
        Rotate(actuator_, false);
        break;
      case SDL_SCANCODE_K:
        if (r_rotate_button_down) break;
        r_rotate_button_down = true;
        Rotate(actuator_, true);
        break;
      case SDL_SCANCODE_L:
        if (hold_button_down) break;
        hold_button_down = true;
        Hold(actuator_);
        break;
      default: break;
    }
  } else if (event.type == SDL_EventType::SDL_KEYUP) {
    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_A:
        left_button_down = false;
        transform_ = Vec2(1, 0);
        break;
      case SDL_SCANCODE_S:
        soft_down_button_down = false;
        actuator_.falling_interval *= 20;
        break;
      case SDL_SCANCODE_D:
        right_button_down = false;
        transform_ = Vec2(-1, 0);
        break;
      case SDL_SCANCODE_W:
        hard_down_button_down = false;
        break;
      case SDL_SCANCODE_J:
        l_rotate_button_down = false;
        break;
      case SDL_SCANCODE_K:
        r_rotate_button_down = false;
        break;
      case SDL_SCANCODE_L:
        hold_button_down = false;
        break;
      default: break;
    }
  }
}
TheGame::TheGame(GameWindow *game_window) : Scene(game_window), main_matrix(graphics_->CreateMatrix()), actuator_(nullptr) {
  main_matrix->coord.x = game_window->GetW() / 2;
  Audio::GetInstance().Play_Back();
  main_matrix->coord.y = game_window->GetH() / 2;
  graphics_->SetUpBg();
  actuator_ = TetrisActuator(main_matrix);
  actuator_.graphics_ = graphics_;
  actuator_.SetState(new Generation(false));
  lines = graphics_->CreateScoreBoard();
  lines->coord = {game_window->GetW(), game_window->GetH() / 3 * 2};
  lines->title->SetTxt("Line");
  score = graphics_->CreateScoreBoard();
  time_stamp = graphics_->CreateScoreBoard();
  time_stamp->coord = {game_window->GetW(), game_window->GetH() / 3 * 2 - 200};
  time_stamp->title->SetTxt("time");
}
