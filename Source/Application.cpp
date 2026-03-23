#include "Application.h"

#include <cassert>

#include "GameEntity.h"
#include "Sandbox.h"

Application* Application::_instance = nullptr;

Application::Application() :
	_window(sf::VideoMode({ 800, 600 }), "SFML3Template")
{
	_instance = this;

	_window.setVerticalSyncEnabled(true);
    _window.setKeyRepeatEnabled(false);
}

bool Application::IsWindowOpen()
{
    return _window.isOpen();
}

void Application::ProcessEvents()
{
    _window.handleEvents([this](const auto& type) 
        { 
            this->HandleEvent(type); 
        });
}

void Application::Setup()
{
}

void Application::Update()
{
	float dt = _clock.restart().asSeconds();

    for (auto& gameEntity : _gameEntities)
    {
        if (auto& entity = gameEntity)
        {
            entity->Update(dt);
        }
	}
}

void Application::Render()
{
    _window.clear();

	for (auto& gameEntity : _gameEntities)
    {
        if (auto& entity = gameEntity)
        {
            entity->Render(_window);
        }
    }

    _window.display();
}

void Application::AddGameEntity(std::shared_ptr<GameEntity> gameEntity)
{
    _gameEntities.push_back(gameEntity);
    gameEntity->Setup();
}

void Application::RemoveGameEntity(std::shared_ptr<GameEntity> gameEntity)
{ 
    _gameEntities.erase(std::remove(_gameEntities.begin(), _gameEntities.end(), 
        gameEntity), _gameEntities.end());
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