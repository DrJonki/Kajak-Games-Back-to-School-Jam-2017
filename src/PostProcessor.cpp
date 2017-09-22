#include <Jam/PostProcessor.hpp>
#include <Jam/Instance.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace jam
{

  PostProcessor::PostProcessor(Instance& ins)
    : m_instance(ins),
      m_shader(ins.resourceManager.)
  {}


}