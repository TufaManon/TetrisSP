//
// Created by Tufa Manon on 2023/1/27.
//

#ifndef TETRIS_GRAPHICS_H_
#define TETRIS_GRAPHICS_H_
#include "font.h"
#include "game-window.h"
#include "scene/matrix.h"
#include "string"
#include "texture.h"
#include "tty.h"
#include <list>
#include <map>
struct Button {
  Vec2 coord;
  int w = 0, h = 0;
};
struct ScoreBoard {
  ScoreBoard(Font *title, Font *message);
  ~ScoreBoard();
  Vec2 coord;
  Font *title;
  Font *message;
  double scale = 1;
};
class Graphics {
 public:
  explicit Graphics(GameWindow *game_window);
  ~Graphics();
  void Render();
  Button *CreateButton();
  Matrix *CreateMatrix();
  ScoreBoard *CreateScoreBoard();
  void SetUpBg();

 private:
  void DrawMatrix(Matrix *matrix);
  void DrawScoreBoard(ScoreBoard *score_board);
  void LoadMinos();
  void LoadScoreBoard();
  std::map<std::string, Texture *> texture_map;
  std::list<Button *> buttons_;
  std::list<SDL_Texture *> sources_;
  std::list<Matrix *> matrix_;
  std::list<ScoreBoard *> score_boards_;
  GameWindow *game_window_;
  TTF_Font *font_;
  bool bg_flag = false;
};

#endif//TETRIS_GRAPHICS_H_