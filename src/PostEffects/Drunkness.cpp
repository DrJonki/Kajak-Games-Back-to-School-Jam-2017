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
  }
}