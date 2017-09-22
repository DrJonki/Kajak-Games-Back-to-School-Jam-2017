#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

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

    void update(const float delta);

    void render();

  private:

    Instance& m_instance;
    sf::Shader& m_shader;
    sf::RectangleShape m_quad;
  };
}