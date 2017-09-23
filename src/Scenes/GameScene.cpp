#include <Jam/Scenes/GameScene.hpp>
#include <Jam/Layer.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Player.hpp>
#include <Jam/Entities/Mushroom.hpp>
#include <Jam/Entities/BackgroundSprite.hpp>
#include <Jam/PostEffects/Drunkness.hpp>
#include <Jam/PostEffects/BlackHole.hpp>
#include <Jam/Randomizer.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace
{
  const float ns_stripHeight = 70.f;
}

namespace jam
{
  GameScene::GameScene(Instance& ins)
    : Scene(ins),
      m_background(),
      m_backgroundLayer(addLayer(5)),
      m_gameLayer(addLayer(20)),
      m_shroomLayer(addLayer(10)),
      m_player(m_gameLayer.insert<Player>("Player", ins)),
      m_camera(),
      m_timer(0),
      m_scoreText("Score: 0", ins.resourceManager.GetFont("RockSalt-Regular.ttf")),
      m_gameoverTimer(ins.config.float_("LOSE_TIMER_ROOF"))
  {
    const auto camSize = sf::Vector2f(ins.config.float_("VIEW_X"), ins.config.float_("VIEW_Y"));
    m_camera = sf::View(sf::Vector2f(camSize.x * 0.5f, camSize.y * 2.5f), camSize);

    m_backgroundLayer.setSharedView(&m_camera);
    m_gameLayer.setSharedView(&m_camera);
    m_shroomLayer.setSharedView(&m_camera);

    for (std::size_t i = 0u; camSize.y * 5.f > (i + 1) * ns_stripHeight; ++i) {
      auto& bk = m_backgroundLayer.insert<BackgroundSprite>(std::to_string(i));
      m_background.push_back(&bk);

      bk.setSize(sf::Vector2f(camSize.x * 5.f, ns_stripHeight));
      bk.setOrigin(bk.getLocalBounds().width * 0.5f, 0);
      bk.setFillColor(sf::Color(i % 2 == 0 ? 0x6EB257FF : 0xC5E063FF));
    }

    m_player.setScale(0.5f, 0.5f);
    m_player.setOrigin(sf::Vector2f(m_player.getLocalBounds().width, m_player.getLocalBounds().height) * 0.5f);
    m_player.setPosition(m_camera.getCenter());

    // UI
    m_scoreText.setOutlineThickness(2.f);
    m_scoreText.setPosition(10.f, 10.f);

    m_timeRect.setFillColor(sf::Color::Red);
    m_timeRect.setOutlineThickness(1.f);
    m_timeRect.setSize(sf::Vector2f(camSize.x * 0.4f, 10.f));
    m_timeRect.setOrigin(m_timeRect.getLocalBounds().width, 0.f);
    m_timeRect.setPosition(camSize.x - 10.f, 10.f);

    // Post effects
    ins.postProcessor.createEffect<Drunkness>("Drunkness" ,"post-process.vert", "post-process.frag").setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "post-process.vert", "black-hole.frag").setActive(true);
  }

  void GameScene::update(const float delta)
  {
    static const float loseTimerRoof = getInstance().config.float_("LOSE_TIMER_ROOF");

    m_timer += delta;

    if ((m_gameoverTimer -= delta) < 0.f) {
      getInstance().window.close();
      return;
    }

    m_timeRect.setScale(std::max(0.f, m_gameoverTimer / loseTimerRoof), 1.f);

    // Spawn mushrooms & detect collisions
    {
      static const float freq = getInstance().config.float_("MUSHROOM_SPAWN_FREQ");
      static Randomizer rand;

      if (rand.range(0.0f, 1.0f) <= freq) {
        auto& shroom = m_shroomLayer.insert<Mushroom>("", getInstance());

        shroom.setPosition(
          rand.range(m_camera.getCenter().x - m_camera.getSize().x * 0.45f, m_camera.getCenter().x + m_camera.getSize().x * 0.45f),
          m_camera.getCenter().y - m_camera.getSize().y * 0.5f - shroom.getGlobalBounds().height
        );
      }

      for (auto& i : m_shroomLayer.getAll()) {
        auto& shroom = *static_cast<Mushroom*>(i);

        const bool playerCollided = m_player.checkCollision(shroom);
        if (
          playerCollided ||
          shroom.getPosition().y > m_camera.getCenter().y + m_camera.getSize().y * 0.5f
        ) {
          i->erase();

          if (playerCollided) {
            static const float incr = getInstance().config.float_("MUSHROOM_INTENSITY_INCREMENT");

            getInstance().tripping.incrementIntensity(incr);
            m_scoreText.setString("Score: " + std::to_string(static_cast<int>(getInstance().tripping.getIntensity() / incr)));

            m_gameoverTimer = loseTimerRoof;
          }
        }
      }
    }

    // Base update
    Scene::update(delta);

    // Update background positions
    {
      for (std::size_t i = 0u; i < m_background.size(); ++i) {
        static const float speed = getInstance().config.float_("BACKGROUND_SCROLL_SPEED");

        m_background[i]->setPosition(
          m_camera.getCenter().x,
          i * ns_stripHeight + std::fmod(m_timer * speed * ns_stripHeight, ns_stripHeight * 2)
        );
      }
    }

    // Constrain player to screen
    {
      const auto b = m_player.getGlobalBounds();

      const float minX = m_camera.getCenter().x - m_camera.getSize().x * 0.5f + b.width * 0.5f;
      const float maxX = m_camera.getCenter().x + m_camera.getSize().x * 0.5f - b.width * 0.5f;
      const float minY = m_camera.getCenter().y - m_camera.getSize().y * 0.5f + b.height * 0.5f;
      const float maxY = m_camera.getCenter().y + m_camera.getSize().y * 0.5f - b.height * 0.5f;

      m_player.setPosition(
        glm::clamp(m_player.getPosition().x, minX, maxX),
        glm::clamp(m_player.getPosition().y, minY, maxY)
      );
    }
  }

  void GameScene::draw(sf::RenderTarget& target)
  {
    Scene::draw(target);
  }

  void GameScene::postDraw(sf::RenderTarget& target)
  {
    target.setView(target.getDefaultView());

    target.draw(m_scoreText);
    target.draw(m_timeRect);
  }
}