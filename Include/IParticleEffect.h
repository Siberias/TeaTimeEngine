#pragma once

#include <SFML/Graphics.hpp>

#include "IGameEntity.h"

class IParticleEffect : public IGameEntity
{
public:
	~IParticleEffect() = default;

	virtual std::shared_ptr<IParticleEffect> Clone() = 0;

	virtual void Play() = 0;
	virtual void Stop() = 0;

	virtual void SetColour(sf::Color colour) = 0;
	virtual void SetPosition(sf::Vector2f position) = 0;
};

typedef std::shared_ptr<IParticleEffect> IParticleEffectPtr;