#include <Jam/PostProcessor.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Scene.hpp>
#include <Jam/PostEffect.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace jam
{

  PostProcessor::PostProcessor(Instance& ins)
    : m_instance(ins),
      m_effects()
  {
    ins.framebuffer[0].create(ins.window.getSize().x, ins.window.getSize().y);
    ins.framebuffer[1].create(ins.window.getSize().x, ins.window.getSize().y);
  }


  PostProcessor::~PostProcessor()
  {}

  void PostProcessor::clearEffects()
  {
    m_effects.clear();
  }

  void PostProcessor::update(const float delta)
  {
    for (auto& i : m_effects) {
      i->update(delta);
    }
  }

  void PostProcessor::render()
  {
    auto& framebuffer = m_instance.framebuffer;
    auto& window = m_instance.window;
    auto& currentScene = m_instance.currentScene;

    m_quad.setSize(window.getView().getSize());

    window.clear();

    if (currentScene) {
      framebuffer[0].setActive(true);
      framebuffer[0].clear();
      currentScene->draw(framebuffer[0]);
      framebuffer[0].display();

      unsigned int current = 0;
      for (auto& i : m_effects) {
        auto& writeFbo = framebuffer[(current + 1) % 2];
        auto& readFbo = framebuffer[current++ % 2];

        writeFbo.clear();
        writeFbo.setActive();
        m_quad.setTexture(&readFbo.getTexture());
        writeFbo.draw(m_quad, sf::RenderStates(&i->getShader()));
        writeFbo.display();
      }

      m_quad.setTexture(&framebuffer[current % 2].getTexture());

      window.setActive(true);
      window.draw(m_quad);
    }

    window.display();
  }

}