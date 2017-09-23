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
    
    }

  private:

    float m_timer;
  };
}