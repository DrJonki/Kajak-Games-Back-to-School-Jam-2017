#pragma once

namespace jam
{
  class TrippingState
  {
  public:

    TrippingState();

    void update(const float delta);

    float getIntensity() const;

  private:

    float m_intensity;
  };

  TrippingState::TrippingState()
    : m_intensity(0.f)
  {

  }

  void TrippingState::update(const float delta)
  {

  }

  float TrippingState::getIntensity() const
  {
    return m_intensity;
  }

}