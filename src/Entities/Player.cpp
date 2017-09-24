#include <Jam/Entities/Player.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Entities/Mushroom.hpp>
#include <Jam/Scenes/GameScene.hpp>

namespace jam
{

  Player::Player(Instance& ins)
    : AnimatedSprite(ins.resourceManager.GetTexture("badger_delay.png"), 200, 180, 5, 1.f),
      m_instance(ins),
      m_emitter(ins, "star.png", sf::Vector2f(50, 50), 25, 0.1f, 0.5f, 3.f, 0.05f, 20.f, 1.f),
      m_emitter2(ins, "shroom2.png", sf::Vector2f(50, 50), 50, 0.1f, 1.f, 5.f, 0.025f, 20.f, 1.f),
      m_emitter3(ins, "badger_particle.png", sf::Vector2f(200, 180), 3, 0.1f, 2.f, 6.f, 0.025f, 20.f, 2.f)
  {
    
  }

  void Player::update(const float delta)
  {
    const float pitch = static_cast<GameScene&>(*m_instance.currentScene).m_mainMusic.getPitch();
    setSpeed(0.058f * m_instance.config.float_("SPEED_MULT") / pitch);

    AnimatedSprite::update(delta);
    m_emitter.update(delta);
    m_emitter2.update(delta);
    m_emitter3.update(delta);

    static const float speed = m_instance.config.float_("PLAYER_MOVEMENT_SPEED");

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      move(-speed * delta, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      move(speed * delta, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      move(0.f, -speed * delta);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      move(0.f, speed * delta);
  }

  void Player::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
    m_emitter.draw(target);
    m_emitter2.draw(target);
    m_emitter3.draw(target);
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
    const bool coll = scaledRect(getGlobalBounds()).intersects(scaledRect(shroom.getGlobalBounds()));

    if (coll) {
      m_emitter.setPosition(getPosition());
      m_emitter2.setPosition(getPosition());
      m_emitter3.setPosition(getPosition());
      m_emitter.emit();

      if (m_instance.tripping.getIntensity() >= 5.f) {
        m_emitter2.emit();
      }
      if (m_instance.tripping.getIntensity() >= 8.f) {
        m_emitter3.emit();
      }
    }

    return coll;
  }

}