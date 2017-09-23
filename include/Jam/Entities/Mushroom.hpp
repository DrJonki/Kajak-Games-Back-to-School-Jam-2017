#pragma once

#include <Jam/Entity.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace jam
{
  class Player;
  class Instance;

  class Mushroom : public Entity, public sf::Sprite
  {
  public:

    Mushroom(Instance& ins);

  private:

    void update(const float dt) override;

    Instance& m_instance;
  };
}
