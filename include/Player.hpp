#pragma once

#include "raylib-cpp.hpp"

#include "Display.hpp"

class Player {
private:
    Display& m_Display;

    raylib::Texture2D m_Texture;
    raylib::Rectangle m_BoundingRect;

    raylib::Texture2D m_EggTexture;
    raylib::Texture2D m_BrokenEggTexture;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

    float m_Rotation;
    
    int m_Score;
    
    const int LIVES_MAX;
    int m_Lives;

    bool m_Enabled;

public:
    Player(Display& display);

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
    void RenderPlayer();
    void RenderLives();
    void RednerScore();
};