// Scene.h
// A collection of game entities that can be updated and rendered together
#pragma once

#include <vector>

#include "Entities/IGameEntity.h"

class Scene
{
private:
  std::vector<IGameEntityPtr> _gameEntities;
  std::vector<IGameEntityPtr> _unstartedGameEntities;
  std::vector<IGameEntityPtr> _destroyedGameEntities;

public:
  Scene() = default;
  ~Scene() = default;

  void AddGameEntity(IGameEntityPtr entity);
  void RemoveGameEntity(IGameEntityPtr entity);

  IGameEntityPtr FindGameEntityOfType(const std::type_info& typeInfo);
  std::vector<IGameEntityPtr> FindGameEntitiesOfType(
    const std::type_info& typeInfo);

  void Update(const float dt);
  void Render(sf::RenderWindow& window);
  void Destroy();
};