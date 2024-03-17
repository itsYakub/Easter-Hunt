#pragma once

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "Scene.hpp"

#include "Player.hpp"
#include "EggController.hpp"
#include "Display.hpp"
#include "Resources.hpp"

#include "Background.hpp"

#include "Timer.hpp"

class SceneGameplay : public Scene {
private:
    Display& m_Display;
    Resources& m_Resources;
    SceneMenager& m_SceneMenager;

    raylib::Texture2D& m_GameLogo;
    raylib::Texture2D& m_GameOverScreen;
    raylib::Font& m_Font;
    raylib::Music& m_BackgroundMusic;
    raylib::Sound& m_EggCrackSound;

    enum State {
        STATE_BEGIN,
        STATE_GAMEPLAY,
        STATE_GAMEOVER
    } m_GameplayState;

    Player m_Player;
    EggController m_EggController;

    raylib::Vector2 m_LogoPosition;
    raylib::Vector2 m_GameOverScreenPosition;

    Timer m_GameOverCooldownTimer;

    raylib::Text m_TooltipText;
    raylib::Vector2 m_TooltipPosition;

    Background m_Background;

    float m_Volume;
    float m_GameplayTime;
    
public:
    SceneGameplay(Display& display, Resources& resources, SceneMenager& sceneMenager);

    void Update() override;    
    void Render() override;    

private:
    bool GameStarted();
};