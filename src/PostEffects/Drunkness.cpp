#include <Jam/PostEffects/Drunkness.hpp>

namespace jam
{
  Drunkness::Drunkness(Instance& ins, const std::string& name, const std::string& v, const std::string& f)
    : PostEffect(ins, name, v, f),
      m_timer(0.f)
  {}

  void Drunkness::update(const float delta)
  {
    auto& s = getShader();

    s.setUniform("tick", (m_timer += delta));
    s.setUniform("drunkness.positionalWaveLength", sf::Vector2f(0.03f, 0.22f));
    s.setUniform("drunkness.positionalWaveHeight", sf::Vector2f(0.02f, 0.02f));
    s.setUniform("drunkness.standingWaveHeight", sf::Vector2f(0.02f, 0.06f));
    s.setUniform("drunkness.standingFreq", sf::Vector2f(3.5f, 1.f));
    s.setUniform("drunkness.positionalCompressionRates", sf::Vector2f(0.05f, 0.03f));
  }
}