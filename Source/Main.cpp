#include "Application.h"

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