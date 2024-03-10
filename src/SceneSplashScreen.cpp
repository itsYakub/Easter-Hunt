#include "SceneSplashScreen.hpp"

#include <string>
#include <array>

#include "raylib-cpp.hpp"
#include "raygui.h"

#include "SceneMenager.hpp"
#include "SceneGameplay.hpp"

SceneSplashScreen::SceneSplashScreen(Display& display, SceneMenager& sceneMenager) : 
    m_Display(display),
    m_SceneMenager(sceneMenager),
    m_RaylibLogo("../res/raylib-cpp_256x256.png"),
    m_SwitchSceneTimer(5.0f) {

}

void SceneSplashScreen::Update() {
    m_SwitchSceneTimer.Process(m_Display.GetFrameTime());

    if(m_SwitchSceneTimer.Finished() || raylib::Keyboard::GetKeyPressed()) {
        m_SceneMenager.LoadScene(new SceneGameplay(m_Display, m_SceneMenager));
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

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiLabel(raylib::Rectangle(216.0f, 568.0f, 352.0, 32.0f), "Created with Raylib-cpp.");
} 