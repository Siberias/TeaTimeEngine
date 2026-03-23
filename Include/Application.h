// Application.h
// Wraps an SFML window, provides core game engine functions and reads system events
#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "GameEntity.h"

class Application
{
private:
	static Application* _instance;

	sf::Clock _clock;
	sf::RenderWindow _window;

	//TODO: Move entity management into a Scene
	std::vector<std::shared_ptr<GameEntity>> _gameEntities;

public:
	Application();

	static Application* GetInstance()
	{
		return _instance;
	}

	sf::RenderWindow& GetRenderWindow() { return _window; }

	bool IsWindowOpen();
	void ProcessEvents();

	void Setup();
	void Update();
	void Render();

	//TODO: Move entity management into a Scene
	void AddGameEntity(std::shared_ptr<GameEntity> entity);
	void RemoveGameEntity(std::shared_ptr<GameEntity> entity);

private:
	void HandleEvent(const sf::Event::KeyPressed& event);
	void HandleEvent(const sf::Event::KeyReleased& event);
	void HandleEvent(const sf::Event::Closed& event);
	void HandleEvent(const auto&) {}
};