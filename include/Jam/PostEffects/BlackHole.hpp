#pragma once

#include <Jam/PostEffect.hpp>
#include <iostream>

namespace jam
{
  class BlackHole : public PostEffect
  {
  public:

    BlackHole(Instance& ins, const std::string& name, const std::string& v, const std::string& f, sf::Vector2f primeVec, float mass, float horizon, float active)
      : PostEffect(ins, name, v, f),
      m_timer(0.f),
      m_primeVec(primeVec),
      m_mass(mass),
      m_horizon(horizon),
      m_activeEffect(active)
    {
    }

    void update(const float delta) override {
      // setActive(getInstance().tripping.getIntensity() > getInstance().config.float_("HOLE_TIME"));
      setActive(getInstance().tripping.getIntensity() > m_activeEffect);
      sf::Shader& s = getShader();
      s.setUniform("tick", (m_timer += delta));
      s.setUniform("direction", (-1.f));
      s.setUniform("primeVec", m_primeVec);
      s.setUniform("mass", m_mass);
      s.setUniform("horizon", m_horizon);
      //s.setUniformArray("holepos", vectors, sizeof(vectors) / sizeof(vectors[0]));
    }

  private:
    const sf::Vector2f m_primeVec;
    float m_timer;
    float m_mass;
    float m_horizon;
    float m_activeEffect;
  };
}