#pragma once

#include "IParticleEffectService.h"

#include <unordered_map>

class IGameEntityFactory;

class Scene;

class ParticleEffectService : public IParticleEffectService
{
private:
  std::unordered_map<std::string, std::shared_ptr<IGameEntityFactory>> 
    _particleEffectFactories;
  std::unordered_map<std::string, IParticleEffectPtr> _loadedEffects;

public:
  ParticleEffectService();
  ~ParticleEffectService();

  void RegisterGameEntityFactory(const std::string& className,
    std::shared_ptr<IGameEntityFactory> factory) override;
  void UnregisterGameEntityFactory(const std::string& className) override;
  void LoadParticleEffects() override;
  IParticleEffectPtr InstantiateEffect(const std::string& effectName,
    Scene& scene, sf::Vector2f position, bool autoPlay = true) override;

private:
  void LoadParticleEffect(const std::string& particleEffectPath);
};