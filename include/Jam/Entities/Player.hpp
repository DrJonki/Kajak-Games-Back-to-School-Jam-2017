#pragma once

#include <Jam/Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace jam
{
  class Player : public Entity, public sf::RectangleShape
  {
  public:

    Player();

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;
  };
}