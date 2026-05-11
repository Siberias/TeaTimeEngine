#include "SceneLoader.h"

#include <fstream>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;

#include "IGameEntityFactory.h"

SceneLoader::SceneLoader()
{
	//Register game entity factories here
	//e.g. _gameEntityFactories["Player"] = new PlayerFactory();
}

SceneLoader::~SceneLoader()
{
	for (auto& factory : _gameEntityFactories)
	{
		delete factory.second;
	}
}

std::shared_ptr<Scene> SceneLoader::LoadScene(const std::string& scenePath)
{
	std::ifstream fileStream;

	try
	{
		fileStream = std::ifstream(scenePath);
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}
	
	Json sceneJson;

	try
	{
		sceneJson = Json::parse(fileStream);
	}
	catch (const std::exception& e)
	{
		return nullptr;
	}

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	for (Json::iterator it = sceneJson.begin(); it != sceneJson.end(); ++it)
	{
		std::string className = (*it)["class"];

		IGameEntityPtr gameEntity =
			_gameEntityFactories[className]->Create((*it)["data"]);

		scene->AddGameEntity(gameEntity);
	}

	return scene;
}

IGameEntityPtr SceneLoader::CreateGameEntity(const std::string& className,
	std::unordered_map<std::string, std::string> params)
{
	if (_gameEntityFactories.find(className) == _gameEntityFactories.end())
	{
		return nullptr;
	}

	return _gameEntityFactories[className]->Create(params);
}