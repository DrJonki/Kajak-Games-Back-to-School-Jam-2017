#pragma once

#include <Jam/PostEffect.hpp>

namespace jam
{
  class HippieColors : public PostEffect
  {
  public:

    HippieColors(Instance& ins, const std::string& name, const std::string& v, const std::string& f)
      : PostEffect(ins, name, v, f),
        m_timer(0)
    {

    }

    void update(const float delta) override
    {
      auto& s = getShader();

      s.setUniform("tick", (m_timer += delta));
      s.setUniform("modifiableValue", getInstance().tripping.getIntensity());
    }

  private:

    float m_timer;
  };
}