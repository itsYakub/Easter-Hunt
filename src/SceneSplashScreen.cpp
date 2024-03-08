#include "SceneSplashScreen.hpp"

#include <string>
#include <array>

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"
#include "SceneGameplay.hpp"

SceneSplashScreen::SceneSplashScreen(raylib::Window& window, SceneMenager& sceneMenager) : 
    m_Window(window),
    m_SceneMenager(sceneMenager),
    m_RaylibLogo("../res/raylib-cpp_256x256.png"),
    m_SwitchSceneTimer(5.0f) {

}

void SceneSplashScreen::Update() {
    m_SwitchSceneTimer.Process(m_Window.GetFrameTime());

    if(m_SwitchSceneTimer.Finished() || raylib::Keyboard::GetKeyPressed()) {
        m_SceneMenager.LoadScene(new SceneGameplay(m_Window, m_SceneMenager));
    }
}   

void SceneSplashScreen::Render() {
    m_Window.ClearBackground(RAYWHITE);

    m_RaylibLogo.Draw(
        raylib::Rectangle(0, 0, m_RaylibLogo.width, m_RaylibLogo.height),
        raylib::Rectangle(m_Window.GetSize() / 2.0f, m_RaylibLogo.GetSize()),
        raylib::Vector2(m_RaylibLogo.width / 2.0f, m_RaylibLogo.height / 2.0f),
        0.0f, 
        WHITE
    );
} 