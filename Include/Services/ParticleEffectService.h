#pragma once

#include "IParticleEffectService.h"

#include <unordered_map>

class IGameEntityFactory;

class Scene;

class ParticleEffectService : public IParticleEffectService
{
private:
	std::unordered_map<std::string, IGameEntityFactory*> _particleEffectFactories;
	std::unordered_map<std::string, IParticleEffectPtr> _loadedEffects;

public:
	ParticleEffectService();
	~ParticleEffectService();

	void LoadParticleEffects() override;
	IParticleEffectPtr InstantiateEffect(const std::string& effectName,
		Scene& scene, sf::Vector2f position, bool autoPlay = true) override;

private:
	void LoadParticleEffect(const std::string& particleEffectPath);
};