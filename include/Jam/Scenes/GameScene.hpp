#pragma once

#include <Jam/Scene.hpp>
#include <SFML/Graphics/View.hpp>

namespace jam
{
  class Player;

  class GameScene : public Scene
  {
  public:

    GameScene(Instance& ins);

    void update(const float delta) override;

  private:

    Layer& m_gameLayer;
    Player& m_player;
    sf::View m_camera;
  };
}