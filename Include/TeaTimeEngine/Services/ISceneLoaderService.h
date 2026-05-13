#pragma once

#include <memory>
#include <string>

class IGameEntity;
class IGameEntityFactory;
class Scene;
using IGameEntityPtr = std::shared_ptr<IGameEntity>;

class ISceneLoaderService
{
public:
  virtual ~ISceneLoaderService() = default;

  virtual void RegisterGameEntityFactory(const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) = 0;
  virtual void UnregisterGameEntityFactory(const std::string& className) = 0;
  virtual std::shared_ptr<Scene> LoadScene(const std::string& scenePath) = 0;
  virtual IGameEntityPtr CreateGameEntity(const std::string& className,
    std::unordered_map<std::string, std::string> params) = 0;
};