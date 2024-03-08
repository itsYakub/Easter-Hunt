#pragma once

#include "raylib-cpp.hpp"

class Player {
private:
    raylib::Window& m_Window;

    raylib::Texture2D m_Texture;
    raylib::Rectangle m_BoundingRect;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

    float m_Rotation;

    int m_Score;
    int m_Lives;

    bool m_Enabled;

public:
    Player(raylib::Window& window);

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
};