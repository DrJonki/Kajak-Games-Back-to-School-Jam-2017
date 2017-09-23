#include <Jam/Entities/BackgroundSprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace jam
{
  void BackgroundSprite::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
  }
}
