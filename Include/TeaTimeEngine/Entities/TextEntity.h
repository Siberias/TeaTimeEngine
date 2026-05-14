#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "IGameEntity.h"

class TextEntity : public IGameEntity
{
protected:
  sf::Text _sfText;

public:
  TextEntity(const sf::Font& font, const std::string& text);
  ~TextEntity() = default;

  void Setup() override;
  void Start() override;
  void Update(const float dt) override;
  void Render(sf::RenderWindow& window) override;
  void Destroy() override;

  sf::Vector2f GetPosition() const override { return _sfText.getPosition(); }
  void SetPosition(const sf::Vector2f& position) override;

  const std::string& GetText() const { return _sfText.getString(); }
  void SetText(const std::string& text) { _sfText.setString(text); }
};