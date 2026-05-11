#include "Application.h"

#include <stdexcept>

#include "IGameEntity.h"
#include "SceneLoader.h"
#include "Services/FontService.h"
#include "Services/ParticleEffectService.h"

Application* Application::_instance = nullptr;

Application::Application() :
    _window(sf::VideoMode({ 800, 600 }), "SFML3Game")
{
    if (_instance != nullptr)
    {
        throw std::runtime_error("Application is a singleton and an instance"
            " already exists");
    }

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
	SceneLoader sceneLoader;
	std::shared_ptr<Scene> scene = sceneLoader.
        LoadScene("Assets/Scenes/Sandbox.json");
	_scenes.push_back(scene);

	_serviceLocator = std::make_shared<ServiceLocator>();

	auto fontService = std::make_shared<FontService>();
	_serviceLocator->RegisterService<IFontService>(fontService);
	fontService->LoadFonts();

	auto particleEffectService = std::make_shared<ParticleEffectService>();
	_serviceLocator->RegisterService<IParticleEffectService>
        (particleEffectService);
    particleEffectService->LoadParticleEffects();
}

void Application::Update()
{
	float dt = _clock.restart().asSeconds();

    for (auto& scene : _scenes)
    {
        scene->Update(dt);
	}
}

void Application::Render()
{
    _window.clear();

	for (auto& scene : _scenes)
    {
		scene->Render(_window);
    }

    _window.display();
}

void Application::Destroy()
{
    for (auto& scene : _scenes)
    {
        scene->Destroy();
    }
    _scenes.clear();
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
