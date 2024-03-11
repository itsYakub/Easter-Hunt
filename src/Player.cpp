#include "Player.hpp"

#include <array>

#include "raylib-cpp.hpp"

Player::Player(Display& display) : 
    m_Display(display),
    m_Texture("../res/txt/EasterHunt_Bunny.png"),
    m_BoundingRect(m_Display.GetSize().x / 2.0f - m_Texture.width / 2.0f, m_Display.GetSize().y / 2.0f - m_Texture.height / 2.0f, m_Texture.width, m_Texture.height),
    m_EggTexture("../res/txt/EasterHunt_Egg.png"),
    m_BrokenEggTexture("../res/txt/EasterHunt_BrokenEgg.png"),
    m_Gravity(0.0f, 9.81f * 2),
    m_Velocity(0.0f, 0.0f),
    m_Rotation(0.0f),
    m_Score(0),
    LIVES_MAX(5),
    m_Lives(LIVES_MAX),
    m_Enabled(false) { 
        m_Texture.SetFilter(TEXTURE_FILTER_BILINEAR);
        m_EggTexture.SetFilter(TEXTURE_FILTER_BILINEAR);
        m_BrokenEggTexture.SetFilter(TEXTURE_FILTER_BILINEAR);
    }

void Player::OnEnable() {
    m_Velocity.y = -4.0f;
}

void Player::Update() {
    if(!m_Enabled) {
        return;
    }

    // Left - right bounds behaviour
    if(m_BoundingRect.x + m_BoundingRect.width < 0.0f) {
        m_BoundingRect.x = m_Display.GetSize().x + m_BoundingRect.width;
    } else if(m_BoundingRect.x - m_BoundingRect.width > m_Display.GetSize().x) {
        m_BoundingRect.x = 0.0f - m_BoundingRect.width;
    }

    if(m_BoundingRect.y + m_BoundingRect.height >= m_Display.GetSize().y) {
        m_BoundingRect.y = m_Display.GetSize().y - m_BoundingRect.height;
        m_Velocity.y = -12.0f;
    } else if(m_BoundingRect.y < 0.0f) {
        m_BoundingRect.y = Lerp(m_BoundingRect.y, 0.0f, m_Display.GetFrameTime());
    }

    if((raylib::Keyboard::IsKeyDown(KEY_SPACE) || raylib::Keyboard::IsKeyDown(KEY_W) || raylib::Keyboard::IsKeyDown(KEY_UP) || raylib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT)) && m_BoundingRect.y >= 0.0f) {
        m_Velocity.y -= m_Gravity.y * 2.0f * GetFrameTime();
    }

    m_Velocity.x = Lerp(m_Velocity.x, 8.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Display.GetFrameTime());
    m_Rotation = Lerp(m_Rotation, 30.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Display.GetFrameTime());

    m_Velocity += m_Gravity * m_Display.GetFrameTime();
    m_BoundingRect.x += m_Velocity.x;
    m_BoundingRect.y += m_Velocity.y;
}

void Player::Render() {
    RenderLives();
    RednerScore();
    RenderPlayer();
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

void Player::RenderPlayer() {
    m_Texture.Draw(
        raylib::Rectangle(raylib::Vector2::Zero(), m_Texture.GetSize()), 
        raylib::Rectangle(m_BoundingRect.x + m_Texture.width / 2.0f, m_BoundingRect.y + m_Texture.height / 2.0f, m_Texture.width, m_Texture.height), 
        raylib::Vector2(m_Texture.GetSize()) / 2.0f, 
        m_Rotation, 
        WHITE
    );
}

void Player::RenderLives() {
    for(int i = 0; i < LIVES_MAX; i++) {
        if(i + 1 <= m_Lives) {
            m_EggTexture.Draw(
                raylib::Rectangle(raylib::Vector2::Zero(), m_EggTexture.GetSize()),
                raylib::Rectangle(raylib::Vector2(64.0f, m_Display.GetSize().y - 64.0f * (i + 1)), m_EggTexture.GetSize()),
                raylib::Vector2(m_EggTexture.GetSize()) / 2.0f,
                0.0f,
                WHITE
            );
        }

        else {
            m_BrokenEggTexture.Draw(
                raylib::Rectangle(raylib::Vector2::Zero(), m_BrokenEggTexture.GetSize()),
                raylib::Rectangle(raylib::Vector2(64.0f, m_Display.GetSize().y - 64.0f * (i + 1)), m_BrokenEggTexture.GetSize()),
                raylib::Vector2(m_BrokenEggTexture.GetSize()) / 2.0f,
                0.0f,
                WHITE
            );        
        }
    }
}

void Player::RednerScore() {
    if(m_Score > 0) {
        raylib::Text scoreText(TextFormat("Score: %i", m_Score));
        scoreText.spacing = 2;
        scoreText.fontSize = 32;
        scoreText.color = BLACK;
        
        scoreText.Draw(raylib::Vector2(m_Display.GetSize().x / 2.0f - scoreText.MeasureEx().x / 2.0f, 16.0f));
    }
}

