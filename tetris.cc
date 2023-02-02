#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "game-window.h"
#include "scene/game-index.h"
#include "scene/scene.h"
#include <cinttypes>
#include <vector>
#undef main
int main(int flags, char *flagc[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();
  Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 6, 4096);
  auto *game_window = new GameWindow(1600, 900);
  Scene *scene = new GameIndex(game_window);
  bool quit = false;
  uint64_t current_time = SDL_GetTicks64();
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      } else
        scene->HandleEvent(event);
    }
    auto now = SDL_GetTicks64();
    scene->Update(now - current_time);
    current_time = now;
    auto next_scene = scene->GetNextScene();
    if (next_scene != nullptr) {
      delete scene;
      scene = next_scene;
    }
  }
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  return 0;
}