#pragma once

#include <Jam/Scene.hpp>
#include <SFML/Graphics/View.hpp>
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

  private:

    std::vector<BackgroundSprite*> m_background;
    Layer& m_backgroundLayer;
    Layer& m_gameLayer;
    Layer& m_shroomLayer;
    Player& m_player;
    sf::View m_camera;
    float m_timer;
  };
}