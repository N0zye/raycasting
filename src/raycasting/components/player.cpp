#include "player.h"

Player::Player(Map* map)
    : posX(300)
    , posY(300)
    , angle(0)
{
    for (int i = 0; i < 3; i++) {
        BeginDrawing();
        ClearBackground(WHITE);
        map->draw();
        EndDrawing();
        fullSizeMap = LoadImageFromScreen();
    }
}

Player::~Player()
{
    UnloadImage(fullSizeMap);
}

void Player::draw()
{
    DrawCircle((int)posX, (int)posY, 2, RED);
    DrawLine((int)posX, (int)posY, (int)anglePos().x, (int)anglePos().y, RED);
    DrawText(std::to_string((int)angle).c_str(), 900, 100, 20, BLACK);
    DrawFPS(900, 140);
}

void Player::update()
{
    float deltaX = 0;
    float deltaY = 0;
    if (IsKeyDown(KEY_W)) {
        deltaX += 1 * std::cosf(D2R(angle));
        deltaY += -1 * std::sinf(D2R(angle));
    }
    if (IsKeyDown(KEY_S)) {
        deltaX += -1 * std::cosf(D2R(angle));
        deltaY += 1 * std::sinf(D2R(angle));
    }
    if (IsKeyDown(KEY_A)) {
        deltaX += -1 * std::sinf(D2R(angle));
        deltaY += -1 * std::cosf(D2R(angle));
    }
    if (IsKeyDown(KEY_D)) {
        deltaX += 1 * std::sinf(D2R(angle));
        deltaY += 1 * std::cosf(D2R(angle));
    }

    Vector2 mouseDelta = GetMouseDelta();
    SetMousePosition(500, 500);

    angle -= mouseDelta.x / 15;
    angle = (float)fmod(angle, 360.0);
    if (angle < 0.0) {
        angle += 360.0;
    }

    posX += deltaX;
    posY += deltaY;

    limitMovment(deltaX, deltaY); // To avoid going into the walls or out of the map
    // delta params are required to (if necessary) move the player to a "safe" location
}

float Player::getAngle()
{
    return angle;
}
float Player::getPosX()
{
    return posX;
}
float Player::getPosY()
{
    return posY;
}
Image Player::getMapImage()
{
    return fullSizeMap;
}
void Player::limitMovment(float deltaX, float deltaY)
{
    // Checking for a wall on the left
    Color pixel = GetImageColor(fullSizeMap, (int)posX - 2, (int)posY);
    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
        if (deltaX < 0) { // Getting closer to the wall
            posX -= deltaX;
        }
    }
    // Checking for a wall on the right
    pixel = GetImageColor(fullSizeMap, (int)posX + 2, (int)posY);
    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
        if (deltaX > 0) { // Getting closer to the wall
            posX -= deltaX;
        }
    }
    // Checking for a wall above the player
    pixel = GetImageColor(fullSizeMap, (int)posX, (int)posY - 2);
    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
        if (deltaY < 0) { // Getting closer to the wall
            posY -= deltaY;
        }
    }
    // Checking for a wall under the player
    pixel = GetImageColor(fullSizeMap, (int)posX, (int)posY + 2);
    if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
        if (deltaY > 0) { // Getting closer to the wall
            posY -= deltaY;
        }
    }
}

Vector2 Player::anglePos()
{
    float aPosX, aPosY;

    aPosX = posX + 10 * std::cosf(D2R(angle)) * 1;
    aPosY = posY + 10 * std::sinf(D2R(angle)) * -1;

    return Vector2 { aPosX, aPosY };
}
