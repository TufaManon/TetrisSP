#include "scene.h"
void Scene::Update(uint64_t delta) {
  graphics_->Render();
}
Scene::Scene(GameWindow *game_window) : game_window_(game_window) {
  graphics_ = new Graphics(game_window);
}
Scene *Scene::GetNextScene() {
  return next_scene_;
}
Scene::~Scene() {
  delete graphics_;
}