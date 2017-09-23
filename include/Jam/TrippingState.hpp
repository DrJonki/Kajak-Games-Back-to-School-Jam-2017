#pragma once

namespace jam
{
  class TrippingState
  {
  public:

    TrippingState();

    void incrementIntensity(const float incr);

    float getIntensity() const;

  private:

    float m_intensity;
  };
}