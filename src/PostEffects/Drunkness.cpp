#include <Jam/PostEffects/Drunkness.hpp>
#include <cmath>

namespace jam
{
  Drunkness::Drunkness(Instance& ins, const std::string& name, const std::string& v, const std::string& f)
    : PostEffect(ins, name, v, f),
      m_timer(0.f)
  {}

  void Drunkness::update(const float delta)
  {
    auto& s = getShader();
    float intencity = std::min(getInstance().tripping.getIntensity() / 15, 1.8f);

    s.setUniform("tick", (m_timer += delta));
    s.setUniform("drunkness.positionalWaveLength", std::max(intencity, 0.01f) * sf::Vector2f(0.03f, 0.22f));
    s.setUniform("drunkness.positionalWaveHeight", intencity * sf::Vector2f(0.02f, 0.02f));
    s.setUniform("drunkness.standingWaveHeight", intencity * sf::Vector2f(0.02f, 0.06f));
    s.setUniform("drunkness.standingFreq", intencity *sf::Vector2f(3.5f, 1.f));
    s.setUniform("drunkness.positionalCompressionRates", intencity * sf::Vector2f(0.05f, 0.03f));
  }
}