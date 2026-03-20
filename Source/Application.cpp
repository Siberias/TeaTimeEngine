#include "Application.h"

Application::Application() :
	_window(sf::VideoMode({ 800, 600 }), "SFML3Template")
{
	_window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(false);
}

bool Application::IsWindowOpen()
{
    return _window.isOpen();
}

void Application::ProcessEvents()
{
    _window.handleEvents([this](const auto& type) { this->HandleEvent(type); });
}

void Application::Update()
{
}

void Application::Render()
{
    _window.clear();
    _window.display();
}

#pragma region System Event Handling
void Application::HandleEvent(const sf::Event::KeyPressed& event)
{
}

void Application::HandleEvent(const sf::Event::KeyReleased& event)
{
    if (event.code == sf::Keyboard::Key::Escape)
    {
        _window.close();
    }
}

void Application::HandleEvent(const sf::Event::Closed& event)
{
    _window.close();
}
#pragma endregion