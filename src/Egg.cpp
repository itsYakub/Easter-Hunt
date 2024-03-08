#include "Egg.hpp"

#include "raylib-cpp.hpp"

Egg::Egg(raylib::Window& window, raylib::Texture2D& texture, raylib::Color color, float position) : 
m_Window(window),
m_Texture(texture),
m_BoundingRect(position, -128.0f, m_Texture.width, m_Texture.height),
m_Color(color),
m_Gravity(0.0f, 1.6f),
m_Velocity(0.0f, 0.0f) { 
    m_Texture.SetFilter(TEXTURE_FILTER_ANISOTROPIC_16X);
}

void Egg::Update() {
    m_Velocity += m_Gravity * m_Window.GetFrameTime();
    m_BoundingRect.x += m_Velocity.x;
    m_BoundingRect.y += m_Velocity.y;
} 

void Egg::Render() {
    m_Texture.Draw(
        raylib::Rectangle(0.0f, 0.0f, m_Texture.width, m_Texture.height), 
        raylib::Rectangle(m_BoundingRect.x, m_BoundingRect.y, m_Texture.width, m_Texture.height), 
        raylib::Vector2::Zero(), 
        0.0f, 
        m_Color
    );    
}

raylib::Rectangle Egg::GetRectangle() const {
    return m_BoundingRect;
}