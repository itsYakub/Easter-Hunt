#pragma once

#include "raylib-cpp.hpp"

#include "Display.hpp"
#include "Resources.hpp"
#include "Timer.hpp"

class Player {
private:
    Display& m_Display;
    Resources& m_Resources;

    raylib::Texture2D& m_Texture;
    raylib::Rectangle m_BoundingRect;

    raylib::Texture2D& m_EggTexture;
    raylib::Texture2D& m_BrokenEggTexture;

    raylib::Sound& m_SoundBounce;
    raylib::Sound& m_SoundPickup;

    raylib::Font& m_Font;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;
    float m_VelocityFactor;

    float m_Rotation;

    int m_Score;    
    
    const float GRACE_PERIOD_TIME;
    Timer m_GracePeriodTimer;

    const int LIVES_MAX;
    int m_Lives;

    bool m_Enabled;

public:
    Player(Display& display, Resources& resources);

    void OnEnable();
    void Update();
    void Render();

    bool Enabled();
    void Enable();

    raylib::Rectangle GetRectangle() const;

    void IncrementScore();
    void DecrementLives();
    
    int GetScore() const;
    int GetLives() const;

private:
    void UpdateBoundsCheck();
    void UpdateComponents();
    void UpdateMove();

    void RenderPlayer();
    void RenderLives();
    void RednerScore();
};