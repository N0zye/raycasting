#include "map.h"

Map::Map()
{
    image = LoadImage("assets/map.png");
    if (image.height > GetScreenHeight() || image.width > GetScreenWidth() / 2) {
        throw(std::invalid_argument("Image dimensions exceed the maximum allowed (" + std::to_string(GetScreenWidth() / 2) + "x" + std::to_string(GetScreenHeight()) + ")."));
        return;
    }
    if (image.height < 10 || image.width < 10) {
        throw(std::invalid_argument("Image dimensions fall below the minimum allowed (10x10)"));
        return;
    }
    heightProportion = (float)GetScreenHeight() / (float)image.height;
    widthProportion = (float)GetScreenWidth() / 2 / (float)image.width;
    // Check if the proportions are exact (no decimal value) --> we can implement
    // Otherwise we can't implement
    if (heightProportion > (int)heightProportion || widthProportion > (int)widthProportion) {
        throw(std::invalid_argument("Image needs to be proportionate to the window height and half of the window width"));
        return;
    }

    // All the possible error-leading contitions checked, now we can move on
    // Image proportions alredy calculated and ensured to be safe for use
}

Map::~Map()
{
    UnloadImage(image);
}

void Map::draw()
{
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            Color pixel = GetImageColor(image, i, j);

            // Check for non-ground pixel (!= 255)
            if (pixel.r != 255 && pixel.g != 255 && pixel.b != 255) {
                DrawRectangle(i * widthProportion, j * heightProportion, widthProportion, heightProportion, pixel);
            }
        }
    }
}
