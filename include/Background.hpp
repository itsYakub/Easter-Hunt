#pragma once

#include "raylib-cpp.hpp"

#include "Display.hpp"
#include "ColorList.hpp"

class Background {
private:
    Display& m_Display;

    raylib::Texture2D m_Texture;
    raylib::Rectangle m_TextureRect;

    ColorList m_ColorList;
    raylib::Color m_BackgroundColor;

    const int SCROLL_SPEED;

public:
    Background(Display& display);

    void Update();
    void Render();
};