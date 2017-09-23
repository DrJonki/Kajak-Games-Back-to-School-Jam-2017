#pragma once

#include <Jam/Entity.hpp>
#include <Jam/AnimatedSprite.hpp>

namespace jam
{
  class Instance;

  class Player : public Entity, public AnimatedSprite
  {
  public:

    Player(Instance& ins);

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;
  };
}