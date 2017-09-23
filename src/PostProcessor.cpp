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
    const auto camSize = sf::Vector2f(ins.config.float_("VIEW_X"), ins.config.float_("VIEW_Y"));

    for (std::size_t i = 0; i < 2; ++i) {
      ins.framebuffer[0].setView(sf::View(camSize * 0.5f, camSize));
      ins.framebuffer[0].create(ins.window.getSize().x, ins.window.getSize().y);
    }
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
        if (!i->isActive()) {
          continue;
        }

        auto& writeFbo = framebuffer[(current + 1) % 2];
        auto& readFbo = framebuffer[current++ % 2];

        writeFbo.clear();
        writeFbo.setActive();
        m_quad.setTexture(&readFbo.getTexture());
        i->getShader().setUniform("texture", sf::Shader::CurrentTexture);
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