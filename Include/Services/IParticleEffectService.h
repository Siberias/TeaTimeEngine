#pragma once

#include "IParticleEffect.h"

class Scene;

class IParticleEffectService
{
public:
	virtual ~IParticleEffectService() = default;

	virtual void LoadParticleEffects() = 0;
	virtual IParticleEffectPtr InstantiateEffect(const std::string& effectName,
		Scene& scene, sf::Vector2f position, bool autoPlay = true) = 0;
};