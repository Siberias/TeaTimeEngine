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

  virtual sf::Vector2f GetPosition() const = 0;
  virtual void SetPosition(const sf::Vector2f& position) = 0;
};

typedef std::shared_ptr<IGameEntity> IGameEntityPtr;