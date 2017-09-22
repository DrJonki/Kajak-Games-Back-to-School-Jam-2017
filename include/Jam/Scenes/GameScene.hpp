#pragma once

#include <Jam/Scene.hpp>

namespace jam
{
  class GameScene : public Scene
  {
  public:

    GameScene(Instance& ins);

    void update(const float delta) override;

  private:

    Layer& m_gameLayer;
  };
}