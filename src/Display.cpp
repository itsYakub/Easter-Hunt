#include "Display.hpp"

#include <cmath>

#include "raylib-cpp.hpp"

Display::Display(raylib::Window& window) :
    m_Window(window),
    WIDTH(768),
    HEIGHT(768),
    m_RenderTexture(WIDTH, HEIGHT),
    m_SouldClose(false) {
        m_RenderTexture.GetTexture().SetFilter(TEXTURE_FILTER_BILINEAR);
    }

Display::Display(raylib::Window& window, const int width, const int height) :
    m_Window(window),
    WIDTH(width),
    HEIGHT(height),
    m_RenderTexture(WIDTH, HEIGHT),
    m_SouldClose(false) { 
        m_RenderTexture.GetTexture().SetFilter(TEXTURE_FILTER_TRILINEAR);
    }

Display::Display(raylib::Window& window, const int width, const int height, const TextureFilter filter) :
    m_Window(window),
    WIDTH(width),
    HEIGHT(height),
    m_RenderTexture(WIDTH, HEIGHT),
    m_SouldClose(false) { 
        m_RenderTexture.GetTexture().SetFilter(filter);
    }

Display& Display::Update() {
    raylib::Mouse::SetOffset(-(m_Window.GetSize().x - (WIDTH * Scale())) * 0.5f, -(m_Window.GetSize().y - (HEIGHT * Scale())) * 0.5f);
    raylib::Mouse::SetScale(1 / Scale(), 1 / Scale());

    return *this;
}

Display& Display::Begin() {
    m_RenderTexture.BeginMode();

    return *this;
}

Display& Display::End() {
    m_RenderTexture.EndMode();

    m_Window.BeginDrawing().ClearBackground(BLACK);

    m_RenderTexture.GetTexture().Draw(
        raylib::Rectangle(0.0f, 0.0f, WIDTH, HEIGHT * -1.0f),
        raylib::Rectangle((m_Window.GetSize().x - (WIDTH * Scale())) * 0.5f, (m_Window.GetSize().y - (HEIGHT * Scale())) * 0.5f, WIDTH * Scale(), HEIGHT * Scale()),
        raylib::Vector2::Zero(),
        0.0f,
        WHITE
    );

    m_Window.EndDrawing();

    return *this;
}

raylib::Vector2 Display::GetSize() {
    return raylib::Vector2(WIDTH, HEIGHT);
}

float Display::GetFrameTime() {
    return m_Window.GetFrameTime();
}

bool Display::ShouldClose() {
    return m_SouldClose;
}

void Display::CloseCallback() {
    m_SouldClose = true;
}

float Display::Scale() {
    return std::min(m_Window.GetSize().x / WIDTH, m_Window.GetSize().y / HEIGHT);
}
