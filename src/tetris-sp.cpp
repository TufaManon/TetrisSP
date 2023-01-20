// TetrisSP.cpp: define program entry
//
#include <game.h>
int main(int /*flagc*/, char ** /*flags*/) {
  tetris_sp::game::Game::Init();
  tetris_sp::game::Game::Run();

  return 0;
}
