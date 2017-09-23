#include <Jam/TrippingState.hpp>

namespace jam
{

  TrippingState::TrippingState()
    : m_intensity(0.f)
  {

  }

  void TrippingState::incrementIntensity(const float incr)
  {
    m_intensity += incr;
  }

  float TrippingState::getIntensity() const
  {
    return m_intensity;
  }

}