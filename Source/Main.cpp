#include "Application.h"

int main()
{
    Application application = Application();

    while (application.IsWindowOpen())
    {
        application.ProcessEvents();
        application.Update();
        application.Render();
    }
}