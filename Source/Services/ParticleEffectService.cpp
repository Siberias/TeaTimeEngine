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
	if (!std::filesystem::exists(particleEffectsDirectory))
	{
		PLOG_WARNING << "Fonts directory does not exist: " << 
			particleEffectsDirectory << ". ParticleEffects will not be loaded";
		return;
	}

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
	if (!std::filesystem::exists(particleEffectPath))
	{
		throw std::runtime_error("Particle effect file does not exist: " 
			+ particleEffectPath);
	}

	std::ifstream fileStream = std::ifstream(particleEffectPath);
	Json particleEffectJson = Json::parse(fileStream);

	std::string className = particleEffectJson["class"];

	IGameEntityPtr gameEntity = _particleEffectFactories[className]->
		Create(particleEffectJson["data"]);

	std::string effectName = std::filesystem::path(particleEffectPath).stem()
		.string();
	_loadedEffects[effectName] =
		std::dynamic_pointer_cast<IParticleEffect>(gameEntity);

	PLOG_INFO << "Loaded Particle Effect: " << effectName;
}