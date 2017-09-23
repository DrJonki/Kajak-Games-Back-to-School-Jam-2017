#include <Jam/Entities/Mushroom.hpp>
#include <Jam/Instance.hpp>

namespace jam
{
  Mushroom::Mushroom(Instance& ins)
    : Entity(),
      sf::Sprite(ins.resourceManager.GetTexture("shroom.png")),
      m_instance(ins)
  {
    setScale(0.1f, 0.1f);
  }

  void Mushroom::update(const float dt)
  {
    static const float speed = m_instance.config.float_("MUSHROOM_MOVEMENT_SPEED");

    move(0, speed * dt);
  }

  void Mushroom::draw(sf::RenderTarget& target)
  {
    target.draw(*this);
  }

}
