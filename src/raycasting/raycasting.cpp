#include "raycasting.h"

constexpr auto FULL_BLACK_FRACT = 1;
// Used in castRays(), defines the parameter used to calculate the full blackout
// Distance (1 means full blackout at GetScreenHeight()/1)

// Internal functions:
void errorLoop(const std::exception&); // Displays the error
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
        DrawRectangle(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight() / 2, SKYBLUE);
        DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth() / 2, GetScreenHeight() / 2, DARKBROWN);
        castRays(player, 35);
        map->draw();
        player->draw();
        EndDrawing();
    }
}

void castRays(Player* player, float FOV)
{
    float x0 = player->getPosX(), y0 = player->getPosY();
    Image map = player->getMapImage();
    unsigned char colorComp = 0;
    for (float a = 0; a < FOV; a += FOV / GetScreenWidth() / 2) { // Increment to have 1 ray per pixel to draw (half screen)
        float fixedAngle = a - player->getAngle() - FOV / 2;
        if (fixedAngle < 0) {
            fixedAngle += 360;
        }
        if (fixedAngle > 360) {
            fixedAngle -= 360;
        }
        // Calculate the step in x and y direction for the algorithm
        float dx = cosf(D2R(fixedAngle));
        float dy = sinf(D2R(fixedAngle));

        // Initialize variables for algorithm
        float x = x0;
        float y = y0;
        float distanceToWall = 0;
        // Algorithm contains also the drawing
        while (x >= 0 && y >= 0 && x < map.width / 2 && y < map.height) {

            // Check if the current point hits a wall (pixel is non white in the map)
            Color pixelColor = GetImageColor(map, (int)x, int(y));
            if (pixelColor.r != 255 && pixelColor.g != 255 && pixelColor.b != 255) {
                // Ray hits a wall
                DrawLine(x0, y0, x, y, YELLOW);
                distanceToWall = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));

                // Draw 3D projection
                // Calculate wall height based on distance
                // I don't know why but the height (10'000) needs to be big
                float wallHeight = 10000 / distanceToWall;

                // Calculate the top and bottom coordinates of the wall slice on the screen
                float wallTop = (GetScreenHeight() - wallHeight) / 2;
                float wallBottom = wallTop + wallHeight;

                // Draw the wall slice
                if (distanceToWall >= GetScreenHeight() / FULL_BLACK_FRACT) {
                    colorComp = 0;
                } else {

                    colorComp = 255 * (1 - FULL_BLACK_FRACT * (distanceToWall / GetScreenHeight()));
                }
                // Actual drawing
                DrawLine((GetScreenWidth() / 2) * (1 + a / FOV) + 1, wallTop, (GetScreenWidth() / 2) * (1 + a / FOV) + 1, wallBottom, Color { colorComp, colorComp, colorComp, 255 });
                break;
            }
            // Step to the next point
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
