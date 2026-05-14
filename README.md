# TeaTime Engine
A small game engine currently using the SFML framework for rendering and input handling.

# Features
- Simple game loop and game entity lifecycle
- Service locator
  - Services are stored as their interface type.
  - Concrete service implementations can be configured for different platforms or for running tests
- Scenes class for managing groups of entities.
  - Scene format is a list of JSON objects
  - Objects are constructed from the JSON data with factories
- Particle effects
- Text boxes
- Event system
  - Listeners stored as linked lists per event name
  - Events all derive from an interface and you cast the event based on its name to read its data
- CMake build system

# Example main.cpp
```cpp
#include <TeaTimeEngine/Application.h>

int main()
{
  Application application = Application();

  application.Setup();

  while (application.IsWindowOpen())
  {
    application.ProcessEvents();
    application.Update();
    application.Render();
  }

  application.Destroy();
}
```