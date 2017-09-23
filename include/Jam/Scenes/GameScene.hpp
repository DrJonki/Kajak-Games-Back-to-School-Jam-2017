#pragma once

#include <Jam/Scene.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace jam
{
  class Player;

  class GameScene : public Scene
  {
  public:

    GameScene(Instance& ins);

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;

  private:

    sf::RectangleShape m_background;
    Layer& m_gameLayer;
    Player& m_player;
    sf::View m_camera;
  };
}