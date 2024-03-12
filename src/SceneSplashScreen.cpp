#include "SceneSplashScreen.hpp"

#include <string>
#include <array>

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "SceneGameplay.hpp"

SceneSplashScreen::SceneSplashScreen(Display& display, Resources& resources, SceneMenager& sceneMenager) : 
    m_Display(display),
    m_Resources(resources),
    m_SceneMenager(sceneMenager),
    m_RaylibLogo(m_Resources.GetTexture("raylib")),
    m_SwitchSceneTimer(5.0f) {
        
}

void SceneSplashScreen::Update() {
    m_SwitchSceneTimer.Process(m_Display.GetFrameTime());

    if(m_SwitchSceneTimer.Finished() || raylib::Keyboard::GetKeyPressed()) {
        m_SceneMenager.LoadScene(new SceneGameplay(m_Display, m_Resources, m_SceneMenager));
    }
}   

void SceneSplashScreen::Render() {
    ClearBackground(RAYWHITE);
    
    m_RaylibLogo.Draw(
        raylib::Rectangle(0, 0, m_RaylibLogo.width, m_RaylibLogo.height),
        raylib::Rectangle(m_Display.GetSize() / 2.0f, m_RaylibLogo.GetSize()),
        raylib::Vector2(m_RaylibLogo.width / 2.0f, m_RaylibLogo.height / 2.0f),
        0.0f, 
        WHITE
    );

    raylib::Text splashScreenText;
    splashScreenText.SetText("Created with raylib-cpp");
    splashScreenText.SetColor(BLACK);
    splashScreenText.SetFontSize(32);
    splashScreenText.SetSpacing(2);

    splashScreenText.Draw(raylib::Vector2(
            m_Display.GetSize().x / 2.0f - splashScreenText.MeasureEx().x / 2.0f,
            m_Display.GetSize().y / 2.0f + 160.0f
        )
    );
} 