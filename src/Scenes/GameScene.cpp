#include <Jam/Scenes/GameScene.hpp>
#include <Jam/Layer.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Player.hpp>
#include <Jam/PostEffects/Drunkness.hpp>
#include <Jam/PostEffects/BlackHole.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace jam
{
  GameScene::GameScene(Instance& ins)
    : Scene(ins),
      m_gameLayer(addLayer(10)),
      m_player(m_gameLayer.insert<Player>("Player", ins)),
      m_camera(),
      m_background()
  {
    const auto camSize = sf::Vector2f(ins.config.float_("VIEW_X"), ins.config.float_("VIEW_Y"));
    m_camera = sf::View(camSize * 0.5f, camSize);

    m_gameLayer.setSharedView(&m_camera);

    m_background.setSize(camSize * 2.f);
    m_background.setTexture(&ins.resourceManager.GetTexture("skyline.jpg"));

    m_player.setOrigin(sf::Vector2f(m_player.getLocalBounds().width, m_player.getLocalBounds().height) * 0.5f);

    // Post effects
    ins.postProcessor.createEffect<Drunkness>("Drunkness" ,"post-process.vert", "post-process.frag");
    // ins.postProcessor.createEffect<BlackHole>("BlackHole", "post-process.vert", "black-hole.frag");
  }

  void GameScene::update(const float delta)
  {
    Scene::update(delta);

    const glm::vec2 camPos(m_camera.getCenter().x, m_camera.getCenter().y);
    const glm::vec2 playerPos(m_player.getPosition().x, m_player.getPosition().y);
    const glm::vec2 newCamPos = glm::mix(camPos, playerPos, delta * 3);

    m_camera.setCenter(newCamPos.x, newCamPos.y);
  }

  void GameScene::draw(sf::RenderTarget& target)
  {
    target.draw(m_background);

    Scene::draw(target);
  }

}