#include <Jam/Instance.hpp>
#include <Jam/Scene.hpp>
#include <Jam/PostProcessor.hpp>
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
      postProcessor(*this),
      m_clock(),
      m_quad()
  {
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
  }

  Instance::~Instance()
  {

  }

  void Instance::operator ()()
  {
    const auto delta = m_clock.restart().asSeconds();

    if (currentScene)
      currentScene->update(
        delta * config.float_("SPEED_MULT") // Global game speed multiplier
      );

    postProcessor.update(delta),
    postProcessor.render();

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

