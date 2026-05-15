#include <TeaTimeEngine/Entities/FPSDisplayEntity.h>

#include <format>

void FPSDisplayEntity::Setup()
{
  TextEntity::Setup();

  _fpsHistory.fill(60.0f);
}

void FPSDisplayEntity::Start()
{
  TextEntity::Start();
}

void FPSDisplayEntity::Update(const float dt)
{
  TextEntity::Update(dt);

  float fps = 1.0f / dt;
  _fpsHistory[_fpsHistoryIndex] = fps;
  _fpsHistoryIndex = (_fpsHistoryIndex + 1) % _fpsHistory.size();

  float fpsAverage = 0.0f;
  for (unsigned int i = 0; i < _fpsHistory.size(); ++i)
  {
    fpsAverage += _fpsHistory[i];
  }
  fpsAverage /= _fpsHistory.size();

  _sfText.setString("FPS: " + std::format("{:.0f}", fpsAverage));
}

void FPSDisplayEntity::Render(sf::RenderWindow& window)
{
  TextEntity::Render(window);
}

void FPSDisplayEntity::Destroy()
{
  TextEntity::Destroy();
}