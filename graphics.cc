//
// Created by Tufa Manon on 2023/1/27.
//

#include "graphics.h"
#include <SDL_image.h>
#include <fstream>
#include <nlohmann/json.hpp>
namespace {
struct GameFieldJSON {
  struct Region {
    int x, y, w, h;
  };
  int w, h;
  int cell_size;
  Region next_queue;
  Region hold_queue;
  Region playing_field;
};
GameFieldJSON game_field_json;
SDL_Texture *LoadButtonTexture(SDL_Renderer *renderer) {
  return IMG_LoadTexture(renderer, "assets/button_go.png");
}

void LoadGameFieldJSON() {
  std::fstream f("assets/field-info.json");
  nlohmann::json json = nlohmann::json::parse(f);
  game_field_json.w = json["info"]["width"];
  game_field_json.h = json["info"]["height"];
  game_field_json.cell_size = json["info"]["cell size"];
  game_field_json.hold_queue.x = json["hold queue"]["x"];
  game_field_json.hold_queue.y = json["hold queue"]["y"];
  game_field_json.hold_queue.w = json["hold queue"]["width"];
  game_field_json.hold_queue.h = json["hold queue"]["height"];
  game_field_json.next_queue.x = json["next queue"]["x"];
  game_field_json.next_queue.y = json["next queue"]["y"];
  game_field_json.next_queue.w = json["next queue"]["width"];
  game_field_json.next_queue.h = json["next queue"]["height"];
  game_field_json.playing_field.h = json["playing field"]["height"];
  game_field_json.playing_field.x = json["playing field"]["x"];
  game_field_json.playing_field.y = json["playing field"]["y"];
  game_field_json.playing_field.w = json["playing field"]["width"];
}
}// namespace
Graphics::Graphics(GameWindow *game_window) : game_window_(game_window), buttons_(), texture_map(), font_(nullptr) {
  font_ = TTF_OpenFont("assets/comic.ttf", 26);
  LoadScoreBoard();
  /*init button texture*/ {
    SDL_Texture *button_sdl_tex = LoadButtonTexture(game_window->renderer_);
    auto button_tex = new Texture(button_sdl_tex);
    button_tex->w_ = 216;
    button_tex->h_ = 120;
    button_tex->center_x_ = button_tex->w_ / 2;
    button_tex->center_y_ = button_tex->h_ / 2;
    sources_.push_back(button_sdl_tex);
    texture_map["button"] = button_tex;
  }

  {
    LoadGameFieldJSON();
    SDL_Texture *matrix_sdl_tex = IMG_LoadTexture(game_window->renderer_, "assets/game_field.png");
    auto *matrix_tex = new Texture(matrix_sdl_tex);
    matrix_tex->w_ = game_field_json.w;
    matrix_tex->h_ = game_field_json.h;
    sources_.push_back(matrix_sdl_tex);
    texture_map["matrix"] = matrix_tex;
  }

  LoadMinos();
}
void Graphics::Render() {
  game_window_->Clear();
  if (bg_flag) {
    Texture *bg = texture_map["bg"];
    bg->Render(game_window_->renderer_, 0, 0);
  }
  for (const auto &mt : matrix_) {
    DrawMatrix(mt);
  }
  Texture *button_tex = texture_map["button"];
  for (const auto &button : buttons_) {
    button_tex->w_ = button->w;
    button_tex->h_ = button->h;
    button_tex->Render(game_window_->renderer_, button->coord.x, button->coord.y);
  }
  for (const auto &item : score_boards_) {
    DrawScoreBoard(item);
  }
  game_window_->Present();
}
Button *Graphics::CreateButton() {
  auto button = new Button();
  button->w = 216;
  button->h = 120;
  buttons_.push_back(button);
  return button;
}
Graphics::~Graphics() {
  for (const auto &button : buttons_) {
    delete button;
  }
  for (const auto &pair : texture_map) {
    delete pair.second;
  }
  for (const auto &src : sources_) {
    SDL_DestroyTexture(src);
  }
  for (const auto &mat : matrix_) {
    delete mat;
  }
  for (const auto &item : score_boards_) {
    delete item;
  }
  TTF_CloseFont(font_);
}
Matrix *Graphics::CreateMatrix() {
  auto mat = new Matrix();
  matrix_.push_front(mat);
  return mat;
}
void Graphics::DrawMatrix(Matrix *matrix) {
  std::map<TetriminoType, std::string> kColorTypeMap = {
      {O, "yellow"},
      {I, "light blue"},
      {T, "purple"},
      {L, "orange"},
      {J, "blue"},
      {S, "green"},
      {Z, "red"}};
  SDL_Texture *draw_board = SDL_CreateTexture(game_window_->renderer_,
                                              SDL_PIXELFORMAT_ARGB8888,
                                              SDL_TEXTUREACCESS_TARGET, game_field_json.w, game_field_json.h);
  SDL_SetRenderTarget(game_window_->renderer_, draw_board);
  SDL_SetTextureBlendMode(draw_board, SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(game_window_->renderer_, 0, 0, 0, 0);
  SDL_RenderClear(game_window_->renderer_);
  SDL_SetTextureBlendMode(draw_board, SDL_BLENDMODE_BLEND);
  auto ui = texture_map["matrix"];
  ui->Render(game_window_->renderer_, 0, 0);
  int counter = 0;
  for (auto it = matrix->data_.begin(); it != matrix->data_.end(); it++, counter++) {
    int x_counter = 0;
    for (const auto &mino : **it) {
      if (mino != nullptr) {
        auto tex = texture_map[kColorTypeMap[mino->type_] + " b"];
        tex->scale_h_ = tex->scale_w_ = 1;
        tex->Render(game_window_->renderer_,
                    game_field_json.playing_field.x + x_counter * 48,
                    game_field_json.playing_field.y - game_field_json.playing_field.w / 5 + counter * 48);
      }
      x_counter++;
    }
  }
  if (!matrix->next_.empty()) {
    int h_off = game_field_json.next_queue.y + game_field_json.next_queue.h / 6 / 2;
    int w_off = game_field_json.next_queue.x + game_field_json.next_queue.w / 2 - static_cast<int>(static_cast<double>(matrix->cell_size_) * 0.7);
    for (const auto &tetrimino : matrix->next_) {
      if (tetrimino != nullptr) {
        auto ac_tex = texture_map[kColorTypeMap[tetrimino->type_]];
        ac_tex->scale_w_ = ac_tex->scale_h_ = static_cast<double>(matrix->cell_size_) / 48 * 0.7;
        for (const auto &pos : tetrimino->mino_relative_pos_) {
          ac_tex->Render(game_window_->renderer_,
                         w_off + static_cast<int>(pos.x * matrix->cell_size_ * 0.7),
                         h_off + static_cast<int>(pos.y * matrix->cell_size_ * 0.7));
        }
      }
      h_off += game_field_json.next_queue.h / 6;
    }
    if (matrix->active_ != nullptr) {
      auto ac_tex = texture_map[kColorTypeMap[matrix->active_->type_]];
      for (const auto &pos : matrix->active_->mino_relative_pos_) {
        ac_tex->scale_h_ = ac_tex->scale_w_ = 1;
        ac_tex->Render(game_window_->renderer_,
                       game_field_json.playing_field.x + pos.x * 48 + matrix->active_->pos_.x * 48,
                       game_field_json.playing_field.y - game_field_json.playing_field.w / 5 + matrix->active_->pos_.y * 48 + pos.y * 48);
      }
    }
    if (matrix->ghost_ != nullptr && matrix->phase_ == 2) {
      auto ac_tex = texture_map[kColorTypeMap[matrix->ghost_->type_] + " h"];
      for (const auto &pos : matrix->ghost_->mino_relative_pos_) {
        ac_tex->scale_h_ = ac_tex->scale_w_ = 1;
        ac_tex->Render(game_window_->renderer_,
                       game_field_json.playing_field.x + pos.x * 48 + matrix->ghost_->pos_.x * 48,
                       game_field_json.playing_field.y - game_field_json.playing_field.w / 5 + matrix->ghost_->pos_.y * 48 + pos.y * 48);
      }
    }
    Texture texture = Texture(draw_board);
    SDL_SetRenderTarget(game_window_->renderer_, nullptr);
    double scale = matrix->cell_size_ * 10 / static_cast<double>(game_field_json.playing_field.w);
    texture.w_ = ui->w_;
    texture.h_ = ui->h_;
    texture.center_x_ = texture.w_ / 2;
    texture.center_y_ = texture.h_ / 2;
    texture.scale_h_ = texture.scale_w_ = scale;
    texture.Render(game_window_->renderer_, matrix->coord.x, matrix->coord.y);
    SDL_DestroyTexture(draw_board);
  }
}
void Graphics::LoadMinos() {
  std::fstream f("assets/minos-info.json");
  SDL_Texture *sdl_tex = IMG_LoadTexture(game_window_->renderer_, "assets/minos.png");
  nlohmann::json json = nlohmann::json::parse(f);
  std::string names[] = {"red", "orange", "yellow", "green", "light blue", "blue", "purple"};
  int w = json["cell size"];
  int of = json["off"];

  for (const auto &name : names) {
    int x = json[name]["x"];
    int y = json[name]["y"];
    auto *tex = new Texture(sdl_tex, x, y, w, w);
    auto *tex_b = new Texture(sdl_tex, x, y + of, w, w);
    auto *tex_h = new Texture(sdl_tex, x, y + of + of, w, w);
    tex->h_ = tex->w_ = json["cell size"];
    tex_b->h_ = tex_b->w_ = json["cell size"];
    tex_h->h_ = tex_h->w_ = json["cell size"];
    texture_map[name] = tex;
    texture_map[name + " b"] = tex_b;
    texture_map[name + " h"] = tex_h;
  }
  sources_.push_back(sdl_tex);
}
void Graphics::SetUpBg() {
  SDL_Texture *sdl_tex = IMG_LoadTexture(game_window_->renderer_, "assets/bg.png");
  SDL_SetTextureAlphaMod(sdl_tex, 200);
  auto *tex = new Texture(sdl_tex);
  tex->w_ = game_window_->GetW();
  tex->h_ = game_window_->GetH();
  texture_map["bg"] = tex;
  sources_.push_back(sdl_tex);
  bg_flag = true;
}
void Graphics::LoadScoreBoard() {
  SDL_Texture *sdl_texture = IMG_LoadTexture(game_window_->renderer_, "assets/score_board.png");
  auto *tex = new Texture(sdl_texture);
  tex->h_ = 94;
  tex->w_ = 357;
  tex->center_y_ = tex->h_;
  tex->center_x_ = tex->w_;
  texture_map["score board"] = tex;
  sources_.push_back(sdl_texture);
}
ScoreBoard *Graphics::CreateScoreBoard() {
  SDL_Color color{255, 100, 50, 255};
  SDL_Color color_1{210, 210, 210, 255};
  Font *title = new Font("   ", font_, color);
  Font *message = new Font("   ", font_, color_1);
  auto *score_board = new ScoreBoard(title, message);
  score_boards_.push_back(score_board);
  return score_board;
}
void Graphics::DrawScoreBoard(ScoreBoard *score_board) {
  Texture *tex = texture_map["score board"];
  int off = 20;
  tex->scale_h_ = tex->scale_w_ = score_board->scale;
  SDL_Texture *title_tex = score_board->title->GetTexture(game_window_->renderer_);
  SDL_Texture *message_tex = score_board->message->GetTexture(game_window_->renderer_);
  SDL_Rect title_rect{score_board->coord.x - tex->center_x_ + static_cast<int>(off * score_board->scale), score_board->coord.y - tex->center_y_,
                      score_board->title->GetW(), score_board->title->GetH()};
  SDL_Rect message_rect{score_board->coord.x - tex->center_x_ + static_cast<int>(off * score_board->scale), score_board->coord.y - tex->center_y_ + 30,
                        score_board->message->GetW(), score_board->message->GetH()};
  tex->Render(game_window_->renderer_, score_board->coord.x, score_board->coord.y);
  SDL_RenderCopy(game_window_->renderer_, title_tex, nullptr, &title_rect);
  SDL_RenderCopy(game_window_->renderer_, message_tex, nullptr, &message_rect);
}
ScoreBoard::ScoreBoard(Font *title, Font *message) : title(title), message(message) {}
ScoreBoard::~ScoreBoard() {
  delete title;
  delete message;
}
