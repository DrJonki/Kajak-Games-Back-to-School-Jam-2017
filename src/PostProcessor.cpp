#include <Jam/PostProcessor.hpp>
#include <Jam/Instance.hpp>
#include <Jam/Scene.hpp>
#include <Jam/PostEffect.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <cassert>

namespace jam
{
  PostProcessor::PostProcessor(Instance& ins)
    : m_instance(ins),
      m_effects()
  {
    const auto camSize = sf::Vector2f(ins.config.float_("VIEW_X"), ins.config.float_("VIEW_Y"));

    for (std::size_t i = 0; i < 2; ++i) {
      auto& fbo = ins.framebuffer[i];

      fbo.setView(sf::View(camSize * 0.5f, camSize));
      assert(fbo.create(ins.window.getSize().x, ins.window.getSize().y));
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

    window.setView(window.getDefaultView());
    m_quad.setSize(window.getView().getSize());

    if (currentScene) {
      framebuffer[0].clear();
      currentScene->draw(framebuffer[0]);
      framebuffer[0].display();

      bool zero = true;
      for (auto& i : m_effects) {
        if (!i->isActive()) {
          continue;
        }

        zero = !zero;

        auto& writeFbo = framebuffer[!zero];
        auto& readFbo = framebuffer[zero];

        m_quad.setTexture(&readFbo.getTexture());

        writeFbo.setView(window.getDefaultView());
        writeFbo.clear();
        writeFbo.draw(m_quad, sf::RenderStates(&i->getShader()));
        writeFbo.display();
      }

      window.clear();

      m_quad.setTexture(&framebuffer[!zero].getTexture());
      window.draw(m_quad);
    }

  }

}