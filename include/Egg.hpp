#pragma once

#include "raylib-cpp.hpp"
#include "Display.hpp"

class Egg {
private:
    Display& m_Display;

    raylib::Texture2D& m_Texture;
    raylib::Rectangle m_BoundingRect;
    raylib::Color m_Color;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

public:
    Egg(Display& display, raylib::Texture2D& texture, raylib::Color color, float position);
    void Update();  
    void Render();
    raylib::Rectangle GetRectangle() const;
};