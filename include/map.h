#pragma once

#include <raylib.h>
#include <stdexcept>
#include <string>

class Map {
public:
    Map();
    ~Map();
    void draw();

private:
    Image image;
    float heightProportion;
    float widthProportion;
};
