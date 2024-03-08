#include "Player.hpp"

#include "raylib-cpp.hpp"

Player::Player(raylib::Window& window) : 
    m_Window(window),
    m_Texture("../res/txt/EasterHunt_Bunny.png"),
    m_BoundingRect(m_Window.GetSize().x / 2.0f - m_Texture.width / 2.0f, m_Window.GetSize().y / 2.0f - m_Texture.height / 2.0f, m_Texture.width, m_Texture.height),
    m_Gravity(0.0f, 9.81f * 2),
    m_Velocity(0.0f, 0.0f),
    m_Rotation(0.0f),
    m_Score(0),
    m_Lives(3),
    m_Enabled(false) { 
        m_Texture.SetFilter(TEXTURE_FILTER_ANISOTROPIC_16X);
    }

void Player::OnEnable() {
    m_Velocity.y = -4.0f;
}

void Player::Update() {
    if(!m_Enabled) {
        return;
    }

    if(m_BoundingRect.x + m_BoundingRect.width < 0.0f) {
        m_BoundingRect.x = m_Window.GetSize().x + m_BoundingRect.width;
    } else if(m_BoundingRect.x - m_BoundingRect.width > m_Window.GetSize().x) {
        m_BoundingRect.x = 0.0f - m_BoundingRect.width;
    }

    if(m_BoundingRect.y + m_BoundingRect.height >= m_Window.GetSize().y) {
        m_BoundingRect.y = m_Window.GetSize().y - m_BoundingRect.height;
        m_Velocity.y = m_Velocity.y / 1.5f * -1.0f;
    }

    if(raylib::Keyboard::IsKeyDown(KEY_SPACE) && m_BoundingRect.y >= 0.0f) {
        m_Velocity.y -= m_Gravity.y * 2.0f * GetFrameTime();
    }

    m_Velocity.x = Lerp(m_Velocity.x, 8.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Window.GetFrameTime());
    m_Rotation = Lerp(m_Rotation, 30.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Window.GetFrameTime());

    m_Velocity += m_Gravity * m_Window.GetFrameTime();
    m_BoundingRect.x += m_Velocity.x;
    m_BoundingRect.y += m_Velocity.y;
}

void Player::Render() {
    m_Texture.Draw(
        raylib::Rectangle(0.0f, 0.0f, m_Texture.width, m_Texture.height), 
        raylib::Rectangle(m_BoundingRect.x + m_Texture.width / 2.0f, m_BoundingRect.y + m_Texture.height / 2.0f, m_Texture.width, m_Texture.height), 
        raylib::Vector2(m_Texture.width, m_Texture.height) / 2.0f, 
        m_Rotation, 
        WHITE
    );
}

bool Player::Enabled() {
    return m_Enabled;
}

void Player::Enable() {
    m_Enabled = true;
}

raylib::Rectangle Player::GetRectangle() const {
    return m_BoundingRect;
}

void Player::IncrementScore() {
    m_Score++;
}

void Player::DecrementLives() {
    m_Lives--;
}

int Player::GetScore() const {
    return m_Score;
}

int Player::GetLives() const {
    return m_Lives;
}