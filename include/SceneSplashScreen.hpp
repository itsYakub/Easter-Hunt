#pragma once

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "Scene.hpp"

#include "Timer.hpp"

class SceneSplashScreen : public Scene {
private:
    raylib::Window& m_Window;
    SceneMenager& m_SceneMenager;

    raylib::Texture2D m_RaylibLogo;

    Timer m_SwitchSceneTimer;
    
public:
    SceneSplashScreen(raylib::Window& window, SceneMenager& sceneMenager);

    void Update() override;    
    void Render() override;    
};