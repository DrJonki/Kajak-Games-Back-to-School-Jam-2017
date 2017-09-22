#include <Jam/Entities/Player.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace jam
{

  Player::Player()
    : sf::RectangleShape(sf::Vector2f(100, 100))
  {
    setFillColor(sf::Color::Green);
  }

  void Player::update(const float delta)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      move(-1000.f * delta, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      move(1000.f * delta, 0.f);
  }

  void Player::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
  }
}