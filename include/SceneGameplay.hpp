#pragma once

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "Scene.hpp"

#include "Player.hpp"
#include "EggController.hpp"
#include "Display.hpp"

#include "Background.hpp"

class SceneGameplay : public Scene {
private:
    Display& m_Display;
    SceneMenager& m_SceneMenager;

    Player m_Player;
    EggController m_EggController;

    raylib::Texture2D m_GameLogo;
    raylib::Vector2 m_LogoPosition;

    raylib::Text m_TooltipText;
    raylib::Vector2 m_TooltipPosition;

    Background m_Background;
    
public:
    SceneGameplay(Display& display, SceneMenager& sceneMenager);

    void Update() override;    
    void Render() override;    

private:
    bool GameStarted();
};