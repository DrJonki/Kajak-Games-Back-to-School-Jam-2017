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

    s.setUniform("texture", sf::Shader::CurrentTexture);
    s.setUniform("tick", (m_timer += delta));
    s.setUniform("drunknesParams.positionalWaveLength", sf::Vector2f(0.03, 0.22));
    s.setUniform("drunknesParams.positionalWaveHeight", sf::Vector2f(0.02, 0.02));
    s.setUniform("drunknesParams.standingWaveHeight", sf::Vector2f(0.02, 0.06));
    s.setUniform("drunknesParams.standingFreq", sf::Vector2f(3.5, 1));
    s.setUniform("drunknesParams.positionalCompressionRates", sf::Vector2f(0.05, 0.03));
  }
}