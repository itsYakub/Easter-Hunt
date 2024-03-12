#pragma once

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "Scene.hpp"

#include "Timer.hpp"

#include "Display.hpp"
#include "Resources.hpp"

class SceneSplashScreen : public Scene {
private:
    Display& m_Display;
    Resources& m_Resources;
    SceneMenager& m_SceneMenager;

    raylib::Texture2D& m_RaylibLogo;

    Timer m_SwitchSceneTimer;
    
public:
    SceneSplashScreen(Display& display, Resources& resources, SceneMenager& sceneMenager);

    void Update() override;    
    void Render() override;    
};