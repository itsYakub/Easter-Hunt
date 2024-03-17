#include "Player.hpp"

#include <array>

#include "raylib-cpp.hpp"

Player::Player(Display& display, Resources& resources) : 
    m_Display(display),
    m_Resources(resources),
    m_Texture(m_Resources.GetTexture("EasterHunt_Bunny")),
    m_BoundingRect(m_Display.GetSize().x / 2.0f - m_Texture.width / 2.0f, m_Display.GetSize().y / 2.0f - m_Texture.height / 2.0f, m_Texture.width, m_Texture.height),
    m_EggTexture(m_Resources.GetTexture("EasterHunt_Egg")),
    m_BrokenEggTexture(m_Resources.GetTexture("EasterHunt_BrokenEgg")),
    m_SoundBounce(m_Resources.GetSound("EasterHunt_SoundBounce")),
    m_SoundPickup(m_Resources.GetSound("EasterHunt_SoundPickup")),
    m_Font(m_Resources.GetFont("VarelaRound")),
    m_Gravity(0.0f, 9.81f * 2),
    m_Velocity(0.0f, 0.0f),
    m_VelocityFactor(1.0f),
    m_Rotation(0.0f),
    m_Score(0),
    GRACE_PERIOD_TIME(2.0f),
    m_GracePeriodTimer(0.0f),
    LIVES_MAX(5),
    m_Lives(LIVES_MAX),
    m_Enabled(false) { 
        
    }

void Player::OnEnable() {
    m_Velocity.y = -4.0f;
}

void Player::Update() {
    if(!m_Enabled) {
        return;
    }

    UpdateBoundsCheck();
    UpdateComponents();
    UpdateMove();
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
    m_SoundPickup.Play();
}

void Player::DecrementLives() {
    if(m_GracePeriodTimer.Finished()) {
        m_Lives--;
        m_GracePeriodTimer.Restart(GRACE_PERIOD_TIME);
    }
}

int Player::GetScore() const {
    return m_Score;
}

int Player::GetLives() const {
    return m_Lives;
}

void Player::UpdateBoundsCheck() {
    // Left - right bounds behaviour
    if(m_BoundingRect.x + m_BoundingRect.width < 0.0f) {
        m_BoundingRect.x = m_Display.GetSize().x + m_BoundingRect.width;
    } else if(m_BoundingRect.x - m_BoundingRect.width > m_Display.GetSize().x) {
        m_BoundingRect.x = 0.0f - m_BoundingRect.width;
    }

    // Up - down bounds behaviour
    if(m_BoundingRect.y + m_BoundingRect.height >= m_Display.GetSize().y) {
        m_SoundBounce.Play();
        
        m_BoundingRect.y = m_Display.GetSize().y - m_BoundingRect.height;
        m_Velocity.y = m_Velocity.y * -0.5f;
        m_VelocityFactor = 0.8f;
        
        m_Velocity.y = Clamp(m_Velocity.y, m_Velocity.y, -4.0f);
        m_VelocityFactor = Clamp(m_VelocityFactor, 0.85f, 1.0f);
    } else if(m_BoundingRect.y < 0.0f) {
        m_BoundingRect.y = Lerp(m_BoundingRect.y, 0.0f, m_Display.GetFrameTime());
    }
}

void Player::UpdateComponents() {
    if((raylib::Keyboard::IsKeyDown(KEY_SPACE) || raylib::Keyboard::IsKeyDown(KEY_W) || raylib::Keyboard::IsKeyDown(KEY_UP) || raylib::Mouse::IsButtonDown(MOUSE_BUTTON_LEFT)) && m_BoundingRect.y >= 0.0f) {
        m_Velocity.y -= m_Gravity.y * 2.0f * m_Display.GetFrameTime() * m_VelocityFactor;
    }

    m_Velocity.x = Lerp(m_Velocity.x, 8.0f * GetInput(), 2.0f * m_Display.GetFrameTime()) * m_VelocityFactor;
    m_Rotation = Lerp(m_Rotation, 30.0f * GetInput(), 2.0f * m_Display.GetFrameTime()) * m_VelocityFactor;
    m_VelocityFactor = Lerp(m_VelocityFactor, 1.0f, 2.0f * m_Display.GetFrameTime());

    m_GracePeriodTimer.Process(m_Display.GetFrameTime());
}

void Player::UpdateMove() {
    m_Velocity += m_Gravity * m_Display.GetFrameTime();
    m_BoundingRect.x += m_Velocity.x;
    m_BoundingRect.y += m_Velocity.y;
}


void Player::RenderPlayer() {
    m_Texture.Draw(
        raylib::Rectangle(raylib::Vector2::Zero(), m_Texture.GetSize()), 
        raylib::Rectangle(m_BoundingRect.x + m_Texture.width / 2.0f, m_BoundingRect.y + m_Texture.height / 2.0f, m_Texture.width, m_Texture.height), 
        raylib::Vector2(m_Texture.GetSize()) / 2.0f, 
        m_Rotation, 
        m_GracePeriodTimer.Finished() ? WHITE : Fade(WHITE, 0.8f)
    );
}

void Player::RenderLives() {
    for(int i = 0; i < LIVES_MAX; i++) {
        if(i + 1 <= m_Lives) {
            m_EggTexture.Draw(
                raylib::Rectangle(raylib::Vector2::Zero(), m_EggTexture.GetSize()),
                raylib::Rectangle(raylib::Vector2(64.0f, m_Display.GetSize().y - 64.0f * (i + 1)), m_EggTexture.GetSize()),
                // raylib::Rectangle(raylib::Vector2(64.0f * (i + 1), m_Display.GetSize().y - 64.0f), m_EggTexture.GetSize()),
                // raylib::Rectangle(raylib::Vector2(64.0f * (i + 1), 64.0f), m_EggTexture.GetSize()),
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
        scoreText.font = m_Font;
        scoreText.fontSize = 32;
        scoreText.color = BLACK;

        scoreText.Draw(raylib::Vector2(m_Display.GetSize().x / 2.0f - scoreText.MeasureEx().x / 2.0f, 16.0f));
    }
}

int Player::GetInput() {
    if(raylib::Keyboard::IsKeyDown(KEY_D) || raylib::Keyboard::IsKeyDown(KEY_RIGHT)) {
        return 1;
    } else if(raylib::Keyboard::IsKeyDown(KEY_A) || raylib::Keyboard::IsKeyDown(KEY_LEFT)) {
        return -1;
    } else {
        return 0;
    }
}
