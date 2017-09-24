#pragma once

#include <Jam/Entity.hpp>
#include <Jam/AnimatedSprite.hpp>
#include <Jam/ParticleEmitter.hpp>

namespace jam
{
  class Instance;
  class Mushroom;

  class Player : public Entity, public AnimatedSprite
  {
  public:

    Player(Instance& ins);

    void update(const float delta) override;

    void draw(sf::RenderTarget& target) override;

    bool checkCollision(const Mushroom& shroom) const;

  private:

    Instance& m_instance;
    mutable ParticleEmitter m_emitter;
    mutable ParticleEmitter m_emitter2;
    mutable ParticleEmitter m_emitter3;
    float m_timer;
  };
}