#include <Jam/Entities/Player.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Mushroom.hpp>

namespace jam
{

  Player::Player(Instance& ins)
    : AnimatedSprite(ins.resourceManager.GetTexture("badger_delay.png"), 200, 180, 5, 0.05f),
      m_instance(ins)
  {

  }

  void Player::update(const float delta)
  {
    AnimatedSprite::update(delta);

    static const float speed = m_instance.config.float_("PLAYER_MOVEMENT_SPEED");

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      move(-speed * delta, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      move(speed * delta, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      move(0.f, -speed * delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      move(0.f, speed * delta);
  }

  void Player::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
  }

  sf::FloatRect scaledRect(const sf::FloatRect& r)
  {
    auto rect = r;
    rect.width *= 0.5f;
    rect.height *= 0.5f;
    return rect;
  }

  bool Player::checkCollision(const Mushroom& shroom) const
  {
    return scaledRect(getGlobalBounds()).intersects(scaledRect(shroom.getGlobalBounds()));
  }

}