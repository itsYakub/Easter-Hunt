#pragma once

#include "raylib-cpp.hpp"

class Display {
private:
    raylib::Window& m_Window;

    const int WIDTH;
    const int HEIGHT;

    raylib::RenderTexture m_RenderTexture;

public:
    Display(raylib::Window& window);
    Display(raylib::Window& window, const int width, const int height);
    Display(raylib::Window& window, const int width, const int height, const TextureFilter filter);

    Display& Update();

    Display& Begin();
    Display& End();

    raylib::Vector2 GetSize();
    float GetFrameTime();

private:
    float Scale();
};