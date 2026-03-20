// Application.h
// Wraps an SFML window, provides core game engine functions and reads system events

#pragma once

#include <SFML/Graphics.hpp>

class Application
{
private:
	sf::RenderWindow _window;

public:
	Application();

	bool IsWindowOpen();
	void ProcessEvents();
	void Update();
	void Render();

private:
	void HandleEvent(const sf::Event::KeyPressed& event);
	void HandleEvent(const sf::Event::KeyReleased& event);
	void HandleEvent(const sf::Event::Closed& event);
	void HandleEvent(const auto&) {}
};