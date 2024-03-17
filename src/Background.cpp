#include "Background.hpp"

Background::Background(Display& display, Resources& resources) :
    m_Display(display),
    m_Resources(resources),
    m_Texture(m_Resources.GetTexture("EasterHunt_Background1")),
    m_TextureRect(raylib::Vector2::Zero(), m_Texture.GetSize()),
    m_ColorList(),
    m_BackgroundColor(m_ColorList.GetRandomColor()),
    SCROLL_DIRECTION(-1, 0),
    SCROLL_SPEED(16.0f) {
        
}

void Background::Update() {
    m_TextureRect.x = Lerp(m_TextureRect.x, m_TextureRect.x + SCROLL_SPEED * SCROLL_DIRECTION.x, m_Display.GetFrameTime());
    m_TextureRect.y = Lerp(m_TextureRect.y, m_TextureRect.y + SCROLL_SPEED * SCROLL_DIRECTION.y, m_Display.GetFrameTime());
    
    // TODO(yakub): Implement scrolling in multiple directions
    if(m_TextureRect.x <= -m_Texture.width / 3.0f) {
       m_TextureRect.x = 0.0f; 
    }
}

void Background::Render() {
    m_Texture.Draw(
        raylib::Rectangle(raylib::Vector2::Zero(), m_Texture.GetSize()),
        m_TextureRect,
        raylib::Vector2::Zero(),
        0.0f,
        m_BackgroundColor
    );
}
