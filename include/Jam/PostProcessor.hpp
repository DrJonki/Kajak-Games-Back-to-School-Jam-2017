#pragma once

#include 

namespace sf
{
  class Shader;
}

namespace jam
{
  class Instance;

  class PostProcessor
  {
  public:

    PostProcessor(Instance& ins);

    void render();

  private:

    Instance& m_instance;
    sf::Shader& m_shader;
    sf::RectangleShape m_quad;
  };
}