#pragma once

#include "map.h"
#include <chrono>
#include <cmath>
#include <raylib.h>
#include <string>
#include <thread>

class Player {
public:
    Player(Map* map);
    ~Player();
    void draw();
    void update();

private:
    float posX, posY;
    float angle;
    Image fullSizeMap;

    void limitMovment(float deltaX, float deltaY);

    Vector2 anglePos();
};
