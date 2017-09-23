#include <Jam/PostEffect.hpp>
#include <Jam/Instance.hpp>

namespace jam
{
  PostEffect::PostEffect(Instance& ins, const std::string& name, const std::string& vertex, const std::string& fragment)
    : m_shader(ins.resourceManager.GetShader(vertex, fragment)),
      m_name(name)
  {

  }

  PostEffect::~PostEffect()
  {

  }

  void PostEffect::update(const float delta)
  {}

  sf::Shader& PostEffect::getShader()
  {
    return m_shader;
  }

  const sf::Shader& PostEffect::getShader() const
  {
    return m_shader;
  }

  const std::string& PostEffect::getName() const
  {
    return m_name;
  }

}