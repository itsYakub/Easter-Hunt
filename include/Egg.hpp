#pragma once

#include "raylib-cpp.hpp"

class Egg {
private:
    raylib::Window& m_Window;

    raylib::Texture2D& m_Texture;
    raylib::Rectangle m_BoundingRect;
    raylib::Color m_Color;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

public:
    Egg(raylib::Window& window, raylib::Texture2D& texture, raylib::Color color, float position);
    void Update();  
    void Render();
    raylib::Rectangle GetRectangle() const;
};