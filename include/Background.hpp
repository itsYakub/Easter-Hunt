#pragma once

#include "raylib-cpp.hpp"

#include "Display.hpp"
#include "ColorList.hpp"

#include "Resources.hpp"

class Background {
private:
    Display& m_Display;
    Resources& m_Resources;

    raylib::Texture2D& m_Texture;
    raylib::Rectangle m_TextureRect;

    ColorList m_ColorList;
    raylib::Color m_BackgroundColor;

    const raylib::Vector2 SCROLL_DIRECTION;
    const int SCROLL_SPEED;

public:
    Background(Display& display, Resources& resources);

    void Update();
    void Render();
};