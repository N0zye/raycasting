#include "raycasting.h"
#include "raylib.h"

#define PLATFORM_WINDOWS

int WinMain()
{
    InitWindow(1024, 512, "raycasting");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    mainLoop();

    CloseWindow();

    return 0;
}
