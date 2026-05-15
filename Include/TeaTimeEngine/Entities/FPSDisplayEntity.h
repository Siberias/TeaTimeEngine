#pragma once

#include <array>

#include "TextEntity.h"

class FPSDisplayEntity : public TextEntity
{
private:
  sf::Clock _clock;
  std::array<float, 60> _fpsHistory{};
  int _fpsHistoryIndex = 0;

public:
  FPSDisplayEntity(const sf::Font& font, const std::string& text)
    : TextEntity(font, text) {}
  ~FPSDisplayEntity() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override 
  { 
    return TextEntity::GetPosition();
  }
  void SetPosition(const sf::Vector2f& position) override 
  { 
    TextEntity::SetPosition(position);
  }
};