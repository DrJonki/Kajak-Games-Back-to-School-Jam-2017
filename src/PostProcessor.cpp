#include <Jam/PostProcessor.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Scene.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace jam
{

  PostProcessor::PostProcessor(Instance& ins)
    : m_instance(ins),
      m_shader(ins.resourceManager.GetShader("post-process.vert", "post-process.frag"))
  {
    ins.framebuffer.create(ins.window.getSize().x, ins.window.getSize().y);
    m_quad.setTexture(&ins.framebuffer.getTexture());
  }


  void PostProcessor::update(const float delta)
  {

  }

  void PostProcessor::render()
  {
    auto& framebuffer = m_instance.framebuffer;
    auto& window = m_instance.window;
    auto& currentScene = m_instance.currentScene;

    framebuffer.clear();
    window.clear();

    if (currentScene) {
      framebuffer.setActive(true);
      currentScene->draw(framebuffer);
      framebuffer.display();

      m_quad.setSize(sf::Vector2f(window.getSize()));

      window.setActive(true);
      window.draw(m_quad);
    }

    window.display();
  }

}