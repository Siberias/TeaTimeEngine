#include "Entities/TextEntity.h"

TextEntity::TextEntity(const sf::Font& font, const std::string& text = "") :
  _sfText(font, text)
{
}

void TextEntity::Setup()
{
}

void TextEntity::Start()
{
}

void TextEntity::Update(const float dt)
{
}

void TextEntity::Render(sf::RenderWindow& window)
{
  window.draw(_sfText);
}

void TextEntity::Destroy()
{
}

void TextEntity::SetPosition(const sf::Vector2f& position)
{
  _sfText.setPosition(position - _sfText.getLocalBounds().size * 0.5f);
}