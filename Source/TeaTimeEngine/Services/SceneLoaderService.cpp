#include "Services/SceneLoaderService.h"

#include <fstream>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

#include "Entities/EntityFactories.h"
#include "Entities/IGameEntityFactory.h"
#include "Scene.h"

SceneLoaderService::SceneLoaderService()
{
}

SceneLoaderService::~SceneLoaderService()
{
}

void SceneLoaderService::RegisterGameEntityFactory(const std::string& className,
  std::shared_ptr<IGameEntityFactory> factory)
{
  _gameEntityFactories[className] = factory;
}

void SceneLoaderService::UnregisterGameEntityFactory(const std::string& className)
{
  _gameEntityFactories.erase(className);
}

std::shared_ptr<Scene> SceneLoaderService::LoadScene(const std::string& scenePath)
{
  if (!std::filesystem::exists(scenePath))
  {
    throw std::runtime_error("Scene file does not exist: " + scenePath);
  }

  std::ifstream fileStream = std::ifstream(scenePath);
  Json sceneJson = Json::parse(fileStream);

  std::shared_ptr<Scene> scene = std::make_shared<Scene>();
  for (Json::iterator it = sceneJson.begin(); it != sceneJson.end(); ++it)
  {
    std::string className = (*it)["class"];

    IGameEntityPtr gameEntity = _gameEntityFactories[className]->
      Create((*it)["data"]);

    scene->AddGameEntity(gameEntity);
  }

  return scene;
}

IGameEntityPtr SceneLoaderService::CreateGameEntity(const std::string& className,
  std::unordered_map<std::string, std::string> params)
{
  if (_gameEntityFactories.find(className) == _gameEntityFactories.end())
  {
    return nullptr;
  }

  return _gameEntityFactories[className]->Create(params);
}