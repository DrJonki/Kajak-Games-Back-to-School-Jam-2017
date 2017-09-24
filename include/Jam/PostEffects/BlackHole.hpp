#pragma once

#include <Jam/PostEffect.hpp>

namespace jam
{
  class BlackHole : public PostEffect
  {
  public:

    BlackHole(Instance& ins, const std::string& name, const std::string& v, const std::string& f) : PostEffect(ins, name, v, f),
      m_timer(0.f){}

    void update(const float delta) override {
      setActive(getInstance().tripping.getIntensity() > getInstance().config.float_("HOLE_TIME"));
      sf::Shader& s = getShader();
      sf::Vector2f vectors[5] = {
        sf::Vector2f(0.5, 0.5), 
        sf::Vector2f(0.0, 0.0),
        sf::Vector2f(0.0, 0.0), 
        sf::Vector2f(0.0, 0.0), 
        sf::Vector2f(0.0, 0.0)
      };
      s.setUniform("tick", (m_timer += delta));
      s.setUniform("direction", (-1.f));
      //s.setUniformArray("holepos", vectors, sizeof(vectors) / sizeof(vectors[0]));
    }

  private:

    float m_timer;
  };
}