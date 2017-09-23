#pragma once

#include <Jam/Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace jam
{
  class BackgroundSprite : public Entity, public sf::RectangleShape
  {
  public:

    void draw(sf::RenderTarget& target) override;
  };
}
