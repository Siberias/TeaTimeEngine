#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

class IGameEntityFactory;
class IParticleEffect;
class Scene;
using IParticleEffectPtr = std::shared_ptr<IParticleEffect>;

class IParticleEffectService
{
public:
  virtual ~IParticleEffectService() = default;

  virtual void RegisterGameEntityFactory(const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) = 0;
  virtual void UnregisterGameEntityFactory(const std::string& className) = 0;
  virtual void LoadParticleEffects() = 0;
  virtual IParticleEffectPtr InstantiateEffect(const std::string& effectName,
    Scene& scene, sf::Vector2f position, bool autoPlay = true) = 0;
};