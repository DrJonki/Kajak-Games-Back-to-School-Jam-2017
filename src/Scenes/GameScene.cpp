#include <Jam/Scenes/GameScene.hpp>
#include <Jam/Layer.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Player.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace jam
{
  GameScene::GameScene(Instance& ins)
    : Scene(ins),
      m_gameLayer(addLayer(10)),
      m_player(m_gameLayer.insert<Player>("Player")),
      m_camera(ins.framebuffer.getDefaultView())
  {
    m_gameLayer.setSharedView(&m_camera);

    m_player.setOrigin(m_player.getSize() * 0.5f);
  }

  void GameScene::update(const float delta)
  {
    Scene::update(delta);

    const glm::vec2 camPos(m_camera.getCenter().x, m_camera.getCenter().y);
    const glm::vec2 playerPos(m_player.getPosition().x, m_player.getPosition().y);
    const glm::vec2 newCamPos = glm::mix(camPos, playerPos, delta * 3);

    m_camera.setCenter(newCamPos.x, newCamPos.y);
  }
}