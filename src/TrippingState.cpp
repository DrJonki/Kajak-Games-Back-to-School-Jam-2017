#include <Jam/TrippingState.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace jam
{

  TrippingState::TrippingState()
    : m_intensity(0.f),
      m_targetIntensity(0.f)
  {

  }

  void TrippingState::reset()
  {
    m_intensity = 0.f;
    m_targetIntensity = 0.f;
  }

  void TrippingState::update(const float dt)
  {
    m_intensity = glm::mix(m_intensity, m_targetIntensity, dt * 1.2f);
    std::cout << m_intensity << std::endl;
  }

  void TrippingState::incrementIntensity(const float incr)
  {
    m_targetIntensity += incr;
  }

  float TrippingState::getIntensity() const
  {
    return m_intensity;
  }
}