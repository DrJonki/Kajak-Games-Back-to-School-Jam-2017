#pragma once

#include <Jam/Scene.hpp>
#include <Jam/Layer.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

namespace jam
{
  class Player;
  class BackgroundSprite;

  class GameScene : public Scene
  {
  public:

    GameScene(Instance& ins);

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;

    void postDraw(sf::RenderTarget& target) override;

    void textEvent(const uint32_t code) override;

  private:

    bool isGameOver() const;

    bool isTripMode() const;

    std::vector<BackgroundSprite*> m_background;
    Layer& m_backgroundLayer;
    Layer& m_gameLayer;
    Layer& m_shroomLayer;
    Player& m_player;
    sf::View m_camera;
    float m_timer;
    float m_gameoverTimer;
    float m_mushRoomForceTimer;

    // UI
    sf::Text m_scoreText;
    sf::Text m_gameoverHint;
    sf::RectangleShape m_timeRect;
  };
}