#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <Jam/ResourceManager.hpp>
#include <Jam/ConfigManager.hpp>
#include <Jam/PostProcessor.hpp>
#include <set>

namespace jam
{
  class Scene;

  class Instance final
  {
    Instance(const Instance&) = delete;
    void operator =(const Instance&) = delete;

  public:

    Instance();

    ~Instance();

    void operator ()();

    bool sendRequest(const std::string& url, std::string& res);

    bool sendPutRequest(const std::string& url, const std::string& body);

  public:

    // Globals
    ConfigManager config;
    sf::RenderWindow window;
    sf::RenderTexture framebuffer[2];
    std::unique_ptr<Scene> currentScene;
    ResourceManager resourceManager;
    std::map<sf::String, int> highscores;
    PostProcessor postProcessor;

  public:

    sf::Clock m_clock;

  private:

    sf::RectangleShape m_quad;
  };
}