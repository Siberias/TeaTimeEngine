// SceneLoader.h
// Loads a scene from a JSON file and creates game entities using factories
// TODO: Replace factories with serialization functions on game entities 
#pragma once

#include <unordered_map>

#include "Services/ISceneLoaderService.h"

class IGameEntityFactory;

class SceneLoaderService : public ISceneLoaderService
{
private:
  std::unordered_map<std::string, std::shared_ptr<IGameEntityFactory>> 
    _gameEntityFactories;

public:
  SceneLoaderService();
  ~SceneLoaderService();

  void RegisterGameEntityFactory(const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) override;
  void UnregisterGameEntityFactory(const std::string& className) override;
  std::shared_ptr<Scene> LoadScene(const std::string& scenePath) override;
  IGameEntityPtr CreateGameEntity(const std::string& className,
    std::unordered_map<std::string, std::string> params) override;
};