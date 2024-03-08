#pragma once

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "Scene.hpp"

#include "Player.hpp"
#include "EggController.hpp"

class SceneGameplay : public Scene {
private:
    Player m_Player;
    EggController m_EggController;

    raylib::Texture2D m_GameLogo;
    raylib::Vector2 m_LogoPosition;

    raylib::Window& m_Window;
    SceneMenager& m_SceneMenager;
    
public:
    SceneGameplay(raylib::Window& window, SceneMenager& sceneMenager);

    void Update() override;    
    void Render() override;    

private:
    bool GameStarted();
};