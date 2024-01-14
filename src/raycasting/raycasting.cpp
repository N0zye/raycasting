#include "raycasting.h"

void errorLoop(const std::exception&);
void castRays(Player* player, float FOV);

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
        castRays(player, 45);
        map->draw();
        player->draw();
        EndDrawing();
    }
}

void castRays(Player* player, float FOV)
{
    float X0 = player->getPosX(), Y0 = player->getPosY();
    Image map = player->getMapImage();

    for (float a = player->getAngle() - FOV / 2; a < player->getAngle() + FOV / 2; a += 0.1f) {
        float fixedAngle = a;
        if (fixedAngle < 0) {
            fixedAngle += 360;
        }
        if (fixedAngle > 360) {
            fixedAngle -= 360;
        }
        // Calculate the step in x and y direction for the DDA algorithm
        float dx = cosf(D2R(fixedAngle));
        float dy = -sinf(D2R(fixedAngle)); // negative i don't know why, probably to fix the wrong raylib FoR

        // Initialize variables for DDA algorithm
        float x = X0;
        float y = Y0;

        // DDA algorithm
        while (x >= 0 && y >= 0 && x < map.width / 2 && y < map.height) {

            // Check if the current point hits a wall (pixel is black in the map)
            Color pixelColor = GetImageColor(map, (int)x, int(y));
            if (pixelColor.r == 0 && pixelColor.g == 0 && pixelColor.b == 0) {
                // Ray hits a wall, draw a line from player to the hit point
                DrawLine(X0, Y0, x, y, YELLOW);
                break;
            }
            // Move to the next point usinfg DDA step
            x += dx;
            y += dy;
        }
    }
}

float D2R(float degAngle)
{
    return degAngle * PI / 180;
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
