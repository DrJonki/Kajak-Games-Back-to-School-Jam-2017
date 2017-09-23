#pragma once

#include <Jam/PostEffect.hpp>

namespace jam
{
  class Drunkness : public PostEffect
  {
  public:

    Drunkness(Instance& ins, const std::string& name, const std::string& v, const std::string& f);

    void update(const float delta) override;

  private:

    float m_timer;
  };
}