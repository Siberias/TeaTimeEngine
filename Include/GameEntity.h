#pragma once

#include <SFML/Graphics.hpp>

class GameEntity
{
public:
	GameEntity() = default;
	~GameEntity() = default;

	bool operator==(const GameEntity& other) const
	{
		return this == &other;
	}

	virtual void Setup() = 0; //TODO: Refactor this to take a scene parameter
	virtual void Update(const float dt) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
};