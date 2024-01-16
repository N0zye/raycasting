[![Release](https://img.shields.io/github/v/release/N0zye/raycasting)](https://github.com/N0zye/raycasting/releases/latest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE.txt)

# Raycasting
C++ semi-3D rendering from a .png map using raycasting. 

![image](https://github.com/N0zye/raycasting/assets/84083205/66642b07-171b-4999-9394-56ca82633429)
(the minimap showing the FOV)

## Rendering 3D using only 2d stripes 1 pixel wide
This C++ project uses [raylib](https://www.raylib.com/) to load a map from a .png file and render the top-down view map with the yellow cone showing the player FOV (field of view) and to render the first person view (on the right side of the window) with various heights using raycasting.

## What is raycasting
(from [Wikipedia](https://www.wikipedia.org/))
In early first person games, raycasting was used to efficiently render a 3D world from a 2D playing field using a simple one-dimensional scan over the horizontal width of the screen.

## Customizing the map
To change the map just replace or modify the 'map.png' int the 'assets' folder.
The map png file needs to be:
- bigger than 10x10
- smaller than the window height and (width/2)
- proportionate to the height and width in such a way that every pixel in the map.png can be converted into a regular amount of pixels in the minimap (window heght / png height should give an integer value with no floating point (same for the width))



## Precompiled Version only for windows(x64): 
### [latest Release](https://github.com/N0zye/raycasting/releases/latest) (Only for Windows(x64))

alternatively you can dowload the source and compile it yourself, the project files contain the raylib file for the MSVC compiler

## Why
Although raylib can handle full 3D rendering better than i did, this was a nice little side project to help <ins>me</ins> improve at coding.
