#include "Application.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

#include "Entities/EntityFactories.h"
#include "Entities/IGameEntity.h"
#include "Services/FontService.h"
#include "Services/ParticleEffectService.h"
#include "Services/SceneLoaderService.h"
#include "Services/SynchronousEventService.h"

Application* Application::_instance = nullptr;

Application::Application() :
  _window(sf::VideoMode({ 800, 600 }), "Tea Time Application")
{
  if (_instance != nullptr)
  {
    throw std::runtime_error("Application is a singleton and an instance"
      " already exists");
  }

  _instance = this;

  _window.setKeyRepeatEnabled(false);
}

bool Application::IsWindowOpen()
{
  return _window.isOpen();
}

void Application::ProcessEvents()
{
  _window.handleEvents([this](const auto& type)
    {
      this->HandleEvent(type);
    });
}

void Application::Setup()
{
  ApplyApplicationConfig();
  CreateAndStartServices();
}

void Application::Update()
{
  float dt = _clock.restart().asSeconds();

  for (auto& scene : _scenes)
  {
    scene->Update(dt);
  }
}

void Application::Render()
{
  _window.clear();

  for (auto& scene : _scenes)
  {
    scene->Render(_window);
  }

  _window.display();
}

void Application::Destroy()
{
  for (auto& scene : _scenes)
  {
    scene->Destroy();
  }
  _scenes.clear();
}

void Application::LoadStartupScene()
{
  if (_startupScenePath.empty() || !std::filesystem::exists(_startupScenePath))
  {
    return;
  }

  auto sceneLoaderService = _serviceLocator->GetService<ISceneLoaderService>();
  std::shared_ptr<Scene> scene = sceneLoaderService->
    LoadScene(_startupScenePath);
  _scenes.push_back(scene);
}

#pragma region System Event Handling
void Application::HandleEvent(const sf::Event::KeyPressed& event)
{
}

void Application::HandleEvent(const sf::Event::KeyReleased& event)
{
  if (event.code == sf::Keyboard::Key::Escape)
  {
    _window.close();
  }
}

void Application::HandleEvent(const sf::Event::Closed& event)
{
  _window.close();
}
#pragma endregion

void Application::ApplyApplicationConfig()
{
  const std::string configPath = "Config/Application.json";
  const std::string engineFallbackScene = 
    "Assets/Scenes/EngineFallbackScene.json";

  if (!std::filesystem::exists(configPath))
  {
    _startupScenePath = engineFallbackScene;
    return;
  }

  std::ifstream fileStream = std::ifstream(configPath);
  Json configJson = Json::parse(fileStream);

  if (configJson.contains("startupScene") == false || 
    configJson["startupScene"] == "")
  {
    _startupScenePath = engineFallbackScene;
  }
  else
  {
    _startupScenePath = configJson["startupScene"];
  }
  
  if (configJson.contains("window") && configJson["window"].is_object())
  {
    auto& windowConfig = configJson["window"];

    if (windowConfig.contains("title") && windowConfig["title"].is_string())
    {
      std::string title = windowConfig["title"];
      _window.setTitle(title);
    }

    if (windowConfig.contains("width") && windowConfig.contains("height") &&
      windowConfig["width"].is_number() && windowConfig["height"].is_number())
    {
      unsigned int width = windowConfig["width"];
      unsigned int height = windowConfig["height"];
      _window.setSize({ width, height });
    }

    if (windowConfig.contains("vsync") && windowConfig["vsync"].is_boolean())
    {
      bool vsync = windowConfig["vsync"];
      _window.setVerticalSyncEnabled(vsync);
    }
  }
}

void Application::CreateAndStartServices()
{
  _serviceLocator = std::make_shared<ServiceLocator>();

  auto eventService = std::make_shared<SynchronousEventService>();
  _serviceLocator->RegisterService<IEventService>(eventService);

  auto fontService = std::make_shared<FontService>();
  _serviceLocator->RegisterService<IFontService>(fontService);

  auto particleEffectService = std::make_shared<ParticleEffectService>();
  _serviceLocator->RegisterService<IParticleEffectService>
    (particleEffectService);

  auto sceneLoaderService = std::make_shared<SceneLoaderService>();
  _serviceLocator->RegisterService<ISceneLoaderService>(sceneLoaderService);

  fontService->LoadFonts();
  sceneLoaderService->RegisterGameEntityFactory("TextEntity",
    std::make_shared<TextEntityFactory>());
  sceneLoaderService->RegisterGameEntityFactory("FPSDisplayEntity",
    std::make_shared<FPSDisplayEntityFactory>());
}