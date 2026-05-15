#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class IGameEntity
{
public:
  virtual ~IGameEntity() = default;

  virtual void Setup() = 0;
  virtual void Start() = 0;
  virtual void Update(const float dt) = 0;
  virtual void Render(sf::RenderWindow& window) = 0;
  virtual void Destroy() = 0;

  virtual bool GetIsEnabled() const = 0;
  virtual void SetIsEnabled(bool isEnabled) = 0;
  virtual sf::Vector2f GetPosition() const = 0;
  virtual void SetPosition(const sf::Vector2f& position) = 0;
};

typedef std::shared_ptr<IGameEntity> IGameEntityPtr;

#define IGAMEENTITY_DECLARATION() \
private: \
  bool _isEnabled = true; \
\
public: \
  bool GetIsEnabled() const override { return _isEnabled; } \
  void SetIsEnabled(bool isEnabled) override { _isEnabled = isEnabled; }