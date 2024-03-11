#include "Background.hpp"

Background::Background(Display& display) :
    m_Display(display),
    m_Texture("../res/txt/EasterHunt_Background1.png"),
    m_TextureRect(raylib::Vector2::Zero(), m_Texture.GetSize()),
    m_ColorList(),
    m_BackgroundColor(m_ColorList.GetRandomColor()),
    SCROLL_SPEED(16.0f) {
        m_Texture.SetFilter(TEXTURE_FILTER_TRILINEAR);
}

void Background::Update() {
    m_TextureRect.x = Lerp(m_TextureRect.x, m_TextureRect.x - SCROLL_SPEED, m_Display.GetFrameTime());

    if(m_TextureRect.x <= m_Texture.width / 2.0f * -1.0f) {
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
