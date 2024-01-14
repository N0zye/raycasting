#include "raycasting.h"

void errorLoop(const std::exception&);

void mainLoop()
{
    // Initializing to nullptr to (maybe) get constructed properly in the try-catch
    Map* map = nullptr;
    try { // Constructor call may throw an exeption for an invalid map size
        map = new Map();
    } catch (const std::invalid_argument& e) {
        errorLoop(e);
        return;
    }

    Player* player = new Player(map);

    while (!WindowShouldClose()) {

        // Updating game objects
        player->update();

        // Drawing game objects
        BeginDrawing();
        ClearBackground(WHITE);
        map->draw();
        player->draw();
        EndDrawing();
    }
}

void errorLoop(const std::exception& e)
{
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Could not start the game", GetScreenWidth() / 2 - MeasureText("Could not start the game", 30) / 2, GetScreenHeight() / 2 - 60 - 30, 30, RED);
        DrawText(e.what(), GetScreenWidth() / 2 - MeasureText(e.what(), 20) / 2, GetScreenHeight() / 2 - 20, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
}
