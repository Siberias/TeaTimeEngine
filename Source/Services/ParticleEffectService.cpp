#include "Services/ParticleEffectService.h"

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
using Json = nlohmann::json;
#include <plog/Log.h>

#include "IGameEntityFactory.h"
#include "Scene.h"

ParticleEffectService::ParticleEffectService()
{
	//Register particle effect factories here
	//e.g. _particleEffectFactories["BurstParticleEffect"] = 
	// new BurstParticleEffectFactory();
}

ParticleEffectService::~ParticleEffectService()
{
	for (auto& factory : _particleEffectFactories)
	{
		delete factory.second;
	}
}

void ParticleEffectService::LoadParticleEffects()
{
	std::string particleEffectsDirectory = "Assets/ParticleEffects";
	for (const auto& entry : std::filesystem::directory_iterator(particleEffectsDirectory))
	{
		if (entry.is_regular_file())
		{
			LoadParticleEffect(entry.path().string());
		}
	}
}

IParticleEffectPtr ParticleEffectService::InstantiateEffect(const std::string&
	effectName, Scene& scene, sf::Vector2f position, bool autoPlay)
{
	for (auto& effect : _loadedEffects)
	{
		if (effect.first != effectName)
		{
			continue;
		}

		IParticleEffectPtr newEffect = effect.second->Clone();

		newEffect->SetPosition(position);

		scene.AddGameEntity(newEffect);

		if (autoPlay)
		{
			newEffect->Play();
		}

		return newEffect;
	}
	
	return nullptr;
}

void ParticleEffectService::LoadParticleEffect(
	const std::string& particleEffectPath)
{
	std::ifstream fileStream;

	try
	{
		fileStream = std::ifstream(particleEffectPath);
	}
	catch (const std::exception& e)
	{
		return;
	}

	Json particleEffectJson;

	try
	{
		particleEffectJson = Json::parse(fileStream);
	}
	catch (const std::exception& e)
	{
		return;
	}

	std::string className = particleEffectJson["class"];

	IGameEntityPtr gameEntity = _particleEffectFactories[className]->
		Create(particleEffectJson["data"]);

	std::string effectName = std::filesystem::path(particleEffectPath).stem()
		.string();
	_loadedEffects[effectName] =
		std::dynamic_pointer_cast<IParticleEffect>(gameEntity);

	PLOG_INFO << "Loaded Particle Effect: " << effectName;
}