#include <Jam/Scenes/GameScene.hpp>
#include <Jam/Layer.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Player.hpp>
#include <Jam/Entities/Mushroom.hpp>
#include <Jam/Entities/BackgroundSprite.hpp>
#include <Jam/PostEffects/Drunkness.hpp>
#include <Jam/PostEffects/BlackHole.hpp>
#include <Jam/PostEffects/HippieColors.hpp>
#include <Jam/Randomizer.hpp>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace
{
  const float ns_stripHeight = 70.f;
  const float ns_minVol = 5.f;

  sf::Font& getFont(jam::Instance& ins)
  {
    return ins.resourceManager.GetFont("RockSalt-Regular.ttf");
  }
}

namespace jam
{
  GameScene::GameScene(Instance& ins, const bool started)
    : Scene(ins),
      m_background(),
      m_backgroundLayer(addLayer(5)),
      m_gameLayer(addLayer(20)),
      m_shroomLayer(addLayer(10)),
      m_player(m_gameLayer.insert<Player>("Player", ins)),
      m_camera(),
      m_timer(0),
      m_scoreText("Score: 0", getFont(ins)),
      m_gameoverTimer(ins.config.float_("LOSE_TIMER_ROOF")),
      m_mushRoomForceTimer(0.f),
      m_gameoverHint(),
      m_mainMusic(),
      m_shroomSound(ins.resourceManager.GetSoundBuffer("shroom.ogg")),
      m_started(started),
      m_startTimer(0.f),
      m_beenGameOver(0.f),
      m_startDuration(ins.config.float_("INFO_SCREEN_DURATION")),
      m_spacePressed(true)
  {
    const float backgroundYScale = 10.f;

    const auto camSize = sf::Vector2f(ins.config.float_("VIEW_X"), ins.config.float_("VIEW_Y"));
    m_camera = sf::View(
      sf::Vector2f(camSize.x * 0.5f, camSize.y * backgroundYScale * 0.5f),
      camSize * (ins.config.boolean("DEBUG_CAMERA") * 10.f + 1.f) * ins.config.float_("FBO_UPSCALE")
     );

    m_backgroundLayer.setSharedView(&m_camera);
    m_backgroundLayer.setActive(false);
    m_gameLayer.setSharedView(&m_camera);
    m_gameLayer.setActive(false);
    m_shroomLayer.setSharedView(&m_camera);
    m_gameLayer.setActive(false);

    for (std::size_t i = 0u; camSize.y * backgroundYScale > (i + 1) * ns_stripHeight; ++i) {
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
    m_timeRect.setPosition(ins.window.getDefaultView().getSize().x - 10.f, 10.f);

    m_gameoverHint[1].setString("Press eny key to restart\n\t\tESCAPE to quit");
    m_gameoverHint[1].setFont(getFont(ins));
    m_gameoverHint[1].setOutlineThickness(1.f);
    m_gameoverHint[1].setOrigin(
      m_gameoverHint[1].getLocalBounds().width / 2,
      m_gameoverHint[1].getLocalBounds().height / 2
    );

    m_gameoverHint[0].setString("You died from withdrawal!");
    m_gameoverHint[0].setFont(getFont(ins));
    m_gameoverHint[0].setOutlineThickness(2.f);
    m_gameoverHint[0].setCharacterSize(36);
    m_gameoverHint[0].setOrigin(
      m_gameoverHint[0].getLocalBounds().width / 2,
      m_gameoverHint[0].getLocalBounds().height / 2
    );

    m_gameStartHint[0].setCharacterSize(46);
    m_gameStartHint[3].setCharacterSize(44);
    m_gameStartHint[0].setString("EPILEPSY\nWARNING!");
    m_gameStartHint[1].setString("You're a badger...");
    m_gameStartHint[2].setString("You must consume mushrooms\n\t\t\tto stay alive");
    m_gameStartHint[3].setString("\t  DISCLAIMER\nDrugs are bad, mkay?");
    m_gameStartHint[4].setString("Use WASD or arrow keys\n\t\t\tto move");

    for (auto& i : m_gameStartHint) {
      i.setFont(getFont(ins));
      i.setCharacterSize(i.getCharacterSize() == 30 ? 36 : i.getCharacterSize());
      i.setOrigin(i.getLocalBounds().width / 2.f, i.getLocalBounds().height / 2.f);
      i.setPosition(ins.window.getDefaultView().getSize() / 2.f);
    }

    // Music
    m_mainMusic.openFromFile("assets/Audio/badger.ogg");
    m_mainMusic.setRelativeToListener(true);
    m_mainMusic.setLoop(true);
    m_mainMusic.setVolume(ns_minVol);
    m_mainMusic.play();

    // Sounds
    m_shroomSound.setRelativeToListener(true);
    m_shroomSound.setVolume(20.f);

    // Post effects
    ins.postProcessor.createEffect<HippieColors>("HippieColors", "basic.vert", "hippie-colors.frag").setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "basic.vert", "black-hole.frag", sf::Vector2f(3, 5), 0.0016f, 0.1f, 6.1f).setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "basic.vert", "black-hole.frag", sf::Vector2f(1.3, 1.7), 0.03f, 0.08f, 10.0f).setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "basic.vert", "black-hole.frag", sf::Vector2f(7, 1.9), 0.3f, 0.025f, 15.0f).setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "basic.vert", "black-hole.frag", sf::Vector2f(2.3, 1.3), 0.3f, 0.02f, 15.0f).setActive(true);
    ins.postProcessor.createEffect<BlackHole>("BlackHole", "basic.vert", "black-hole.frag", sf::Vector2f(3.1, 2.3), 0.3f, 0.01f, 15.0f).setActive(true);
    ins.postProcessor.createEffect<Drunkness>("Drunkness" ,"basic.vert", "drunkness.frag").setActive(true);
  }

  void GameScene::update(const float delta)
  {
    m_mainMusic.setVolume(ns_minVol + m_started * std::min(100.f - ns_minVol, m_mainMusic.getVolume() + delta * 5.f - ns_minVol));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
      m_spacePressed = true;

    if (!m_started && (m_startTimer += delta * m_spacePressed) >= m_gameStartHint.size() * m_startDuration) {
      m_started = true;
    }

    // Intro
    if (!m_started)
    {
      return;
    }
    else {
      m_backgroundLayer.setActive(true);
      m_gameLayer.setActive(true);
      m_gameLayer.setActive(true);
    }

    if (isGameOver()) {
      m_beenGameOver += delta;
    }

    static const float loseTimerRoof = getInstance().config.float_("LOSE_TIMER_ROOF");
    static const float intensityIncrement = getInstance().config.float_("MUSHROOM_INTENSITY_INCREMENT");

    const float intensity = getInstance().tripping.getIntensity() / intensityIncrement;
    const float soundThreshold = 15.f;
    if (intensity >= soundThreshold) {
      const auto pitch = 1.f + std::sin(m_timer * 0.2f) * std::min(0.5f, (intensity - soundThreshold) / 100.f);
      m_mainMusic.setPitch(pitch);
    }

    m_timer += delta;
    m_gameoverTimer -= delta * !isTripMode();

    m_scoreText.setString("Score: " + std::to_string(static_cast<int>(getInstance().tripping.getIntensityTarget() / intensityIncrement)));

    if (isGameOver()) {
      m_player.setActive(false);

      const auto basePos = getInstance().window.getView().getCenter();

      m_scoreText.setCharacterSize(46);
      m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2.f, m_scoreText.getLocalBounds().height / 2.f);
      m_scoreText.setPosition(basePos.x, basePos.y - 60.f);

      m_gameoverHint[0].setPosition(basePos.x, basePos.y - 150.f);
      m_gameoverHint[1].setPosition(basePos.x, basePos.y + 60.f);

      return;
    }

    m_timeRect.setScale(std::max(0.f, m_gameoverTimer / loseTimerRoof), 1.f);

    // Spawn mushrooms & detect collisions
    {
      static const float freq = getInstance().config.float_("MUSHROOM_SPAWN_FREQ");
      static Randomizer rand;

      if (rand.range(0.0f, 1.0f) <= freq || (m_mushRoomForceTimer += delta) >= loseTimerRoof / 2) {
        m_mushRoomForceTimer = 0.f;
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
            getInstance().tripping.incrementIntensity(intensityIncrement);
            m_gameoverTimer = loseTimerRoof;
            m_shroomSound.setPitch(rand.range(0.8f, 1.2f));
            m_shroomSound.play();
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

        m_background[i]->setActive(true);
        m_background[i]->setPosition(
          m_camera.getCenter().x-ns_stripHeight*10,
          i * ns_stripHeight + std::fmod(m_timer * speed * ns_stripHeight, ns_stripHeight * 2)
        );
      }
    }

    // Constrain player to screen
    {
      const auto b = m_player.getGlobalBounds();
      const float scale = getInstance().config.float_("FBO_UPSCALE");

      const float minX = (m_camera.getCenter().x - m_camera.getSize().x / scale * 0.5f + b.width * 0.5f);
      const float maxX = (m_camera.getCenter().x + m_camera.getSize().x / scale * 0.5f - b.width * 0.5f);
      const float minY = (m_camera.getCenter().y - m_camera.getSize().y / scale * 0.5f + b.height * 0.5f);
      const float maxY = (m_camera.getCenter().y + m_camera.getSize().y / scale * 0.5f - b.height * 0.5f);

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

    if (!m_started) {
      target.draw(m_gameStartHint[static_cast<unsigned int>(m_startTimer / m_startDuration)]);
      return;
    }

    if (!isTripMode()) {
      target.draw(m_scoreText);
      target.draw(m_timeRect);
    }

    if (isGameOver()) {
      target.draw(m_gameoverHint[0]);
      target.draw(m_gameoverHint[1]);
    }
  }

  void GameScene::textEvent(const uint32_t code)
  {
    if (code == 27)
      return;

    if (isGameOver() && m_beenGameOver <= 1.f)
      return;

    if (!m_started) {
      m_started = true;
    }

    if (isGameOver()) {
      getInstance().tripping.reset();
      getInstance().postProcessor.clearEffects();
      getInstance().currentScene = std::make_unique<GameScene>(getInstance(), true);
    }
  }

  bool GameScene::isGameOver() const
  {
    return m_gameoverTimer < 0.f;
  }

  bool GameScene::isTripMode() const
  {
    static const bool tripMode = getInstance().config.boolean("TRIP_MODE");
    return tripMode;
  }

}