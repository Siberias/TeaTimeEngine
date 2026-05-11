#include "Scene.h"

void Scene::AddGameEntity(IGameEntityPtr gameEntity)
{
	_unstartedGameEntities.push_back(gameEntity);
    _gameEntities.push_back(gameEntity);
    gameEntity->Setup();
}

void Scene::RemoveGameEntity(IGameEntityPtr gameEntity)
{
	_destroyedGameEntities.push_back(gameEntity);
}

IGameEntityPtr Scene::FindGameEntityOfType(const std::type_info& typeInfo)
{
    for (auto& gameEntity : _gameEntities)
    {
		if (typeid(*gameEntity) == typeInfo)
        {
            return gameEntity;
        }
    }
    return nullptr;
}

std::vector<IGameEntityPtr> Scene::FindGameEntitiesOfType(const std::type_info& typeInfo)
{
    std::vector<IGameEntityPtr> entitiesOfType;

    for (auto& gameEntity : _gameEntities)
    {
        if (typeid(*gameEntity) == typeInfo)
        {
            entitiesOfType.push_back(gameEntity);
        }
    }
    return entitiesOfType;
}

void Scene::Update(const float dt)
{
    for (auto& gameEntity : _unstartedGameEntities)
    {
        gameEntity->Start();
    }
    _unstartedGameEntities.clear();

    for (auto& gameEntity : _gameEntities)
    {
        gameEntity->Update(dt);
    }

    for (auto& gameEntity : _destroyedGameEntities)
    {
        size_t originalSize = _gameEntities.size();
        auto iter = std::remove(_gameEntities.begin(), _gameEntities.end(),
            gameEntity);
        if (iter != _gameEntities.end())
        {
            gameEntity->Destroy();
            _gameEntities.erase(iter, _gameEntities.end());
        }
    }
	_destroyedGameEntities.clear();
}

void Scene::Render(sf::RenderWindow& window)
{
    for (auto& gameEntity : _gameEntities)
    {
        gameEntity->Render(window);
    }
}

void Scene::Destroy()
{
    for (auto& gameEntity : _gameEntities)
    {
        gameEntity->Destroy();
    }

	_gameEntities.clear();
    _unstartedGameEntities.clear();
}