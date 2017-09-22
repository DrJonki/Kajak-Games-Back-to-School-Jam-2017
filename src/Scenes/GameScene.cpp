#include <Jam/Scenes/GameScene.hpp>
#include <Jam/Layer.hpp>
#include <Jam/Entities/Player.hpp>

namespace jam
{
  GameScene::GameScene(Instance& ins)
    : Scene(ins),
      m_gameLayer(addLayer(10))
  {
    m_gameLayer.insert<Player>("Player");
  }

  void GameScene::update(const float delta)
  {
    Scene::update(delta);
  }
}