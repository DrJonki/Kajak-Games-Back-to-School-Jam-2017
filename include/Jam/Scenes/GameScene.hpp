#pragma once

#include <Jam/Scene.hpp>
#include <Jam/Layer.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <vector>
#include <array>

namespace jam
{
  class Player;
  class BackgroundSprite;

  class GameScene : public Scene
  {
    friend class Player;

  public:

    GameScene(Instance& ins, const bool started = false);

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;

    void postDraw(sf::RenderTarget& target) override;

    void textEvent(const uint32_t code) override;

  private:

    bool isGameOver() const;

    bool isTripMode() const;

    static const float StartTiming;

    std::vector<BackgroundSprite*> m_background;
    Layer& m_backgroundLayer;
    Layer& m_gameLayer;
    Layer& m_shroomLayer;
    Player& m_player;
    sf::View m_camera;
    float m_timer;
    float m_gameoverTimer;
    float m_mushRoomForceTimer;
    float m_startTimer;
    float m_beenGameOver;
    bool m_started;

    // Audio
    sf::Music m_mainMusic;
    sf::Sound m_shroomSound;

    // UI
    sf::Text m_scoreText;
    sf::Text m_gameoverHint[3];
    std::array<sf::Text, 4> m_gameStartHint;
    sf::RectangleShape m_timeRect;
  };
}