// SceneLoader.h
// Loads a scene from a JSON file and creates game entities using factories
// TODO: Replace factories with serialization functions on game entities 
#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "IGameEntity.h"
#include "Scene.h"

class IGameEntityFactory;

class SceneLoader
{
private:
	std::unordered_map<std::string, IGameEntityFactory*> _gameEntityFactories;

public:
	SceneLoader();
	~SceneLoader();

	std::shared_ptr<Scene> LoadScene(const std::string& scenePath);
	IGameEntityPtr CreateGameEntity(const std::string& className,
		std::unordered_map<std::string, std::string> params);
};