#pragma once

namespace jam
{
  class TrippingState
  {
  public:

    TrippingState();

    void reset();

    void update(const float dt);

    void incrementIntensity(const float incr);

    float getIntensity() const;

  private:

    float m_intensity;
    float m_targetIntensity;
  };
}