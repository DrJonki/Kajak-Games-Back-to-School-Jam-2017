#include <Jam/Instance.hpp>
#include <Jam/Scene.hpp>
#include <SFML/Window/Event.hpp>
#include <rapidjson/document.h>
#include <iostream>
#include <string>

sf::VideoMode getVideomode(const jam::ConfigManager& config) {
  #ifdef _DEBUG
    return sf::VideoMode(config.integer("VIEW_X"), config.integer("VIEW_Y"));
  #else
    return sf::VideoMode::getDesktopMode();
  #endif
}

sf::Uint32 getStyle() {
  #ifdef _DEBUG
    return sf::Style::Default;
  #else
    return sf::Style::None;
  #endif
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

namespace jam
{
  Instance::Instance()
    : config(),
      window(getVideomode(config), "Jam", getStyle()),
      framebuffer(),
      currentScene(),
      resourceManager(),
      highscores(),
      m_clock(),
      m_quad()
  {
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    framebuffer.create(window.getSize().x, window.getSize().y);
    m_quad.setTexture(&framebuffer.getTexture());
  }

  Instance::~Instance()
  {

  }

  void Instance::operator ()()
  {
    if (currentScene)
      currentScene->update(
        m_clock.restart().asSeconds() *
        config.float_("SPEED_MULT") // Global game speed multiplier
      );

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

    // Handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::Resized:
      {
        const auto view = window.getView().getSize();
        const auto ratio = view.x / view.y;
        window.setSize(sf::Vector2u(
          static_cast<unsigned int>(window.getSize().y * ratio),
          window.getSize().y
        ));
        break;
      }
      case sf::Event::KeyReleased:
      {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();

        break;
      }
      case sf::Event::TextEntered:
      {
        currentScene->textEvent(event.text.unicode);
        break;
      }
      }
    }
  }
}

