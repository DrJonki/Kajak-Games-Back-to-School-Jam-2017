#include <Jam/Entities/BackgroundSprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace jam
{

  BackgroundSprite::BackgroundSprite()
    : Entity(),
      sf::RectangleShape()
  {
  }

  void BackgroundSprite::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
  }
}
