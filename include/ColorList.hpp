#pragma once

#include <array>

#include "raylib-cpp.hpp"

struct ColorList {
    const std::array<raylib::Color, 8> Colors;

    ColorList();
    raylib::Color GetColor(int index);
    raylib::Color GetRandomColor();
};