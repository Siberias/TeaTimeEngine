// Application.h
// Wraps an SFML window and provides core game engine functions
#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "IGameEntity.h"
#include "Services/ServiceLocator.h"
#include "Scene.h"

class Application
{
private:
	static Application* _instance;

	sf::Clock _clock;
	sf::RenderWindow _window;

	std::shared_ptr<ServiceLocator> _serviceLocator;

	std::vector<std::shared_ptr<Scene>> _scenes;

public:
	Application();
	~Application() { _instance = nullptr; }

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
	void Destroy();

	const std::vector<std::shared_ptr<Scene>>& GetScenes() const 
	{ return _scenes; }

private:
	void HandleEvent(const sf::Event::KeyPressed& event);
	void HandleEvent(const sf::Event::KeyReleased& event);
	void HandleEvent(const sf::Event::Closed& event);
	void HandleEvent(const auto&) {}
};
