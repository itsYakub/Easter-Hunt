#include "SceneGameplay.hpp"

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"

SceneGameplay::SceneGameplay(raylib::Window& window, SceneMenager& sceneMenager) : 
    m_Player(window),
    m_EggController(window),
    m_GameLogo("../res/txt/EasterHunt_Logo.png"),
    m_LogoPosition(0.0f, 0.0f),
    m_Window(window),
    m_SceneMenager(sceneMenager) {
        m_LogoPosition = raylib::Vector2(m_Window.GetSize().x / 2.0f, 128.0f);
}

void SceneGameplay::Update() {
    if(IsKeyPressed(KEY_SPACE) && (!GameStarted())) {
        m_Player.Enable();
        m_Player.OnEnable();

        m_EggController.Enable();
    }

    else if(GameStarted()) {
        m_LogoPosition.y = Lerp(m_LogoPosition.y, -m_GameLogo.height, 0.8f * GetFrameTime());
    }

    m_Player.Update();
    m_EggController.Update();

    for(int i = 0; i < m_EggController.GetEggList().size(); i++) {
        auto egg = m_EggController.GetEggList().at(i).get();

        if(m_Player.GetRectangle().CheckCollision(egg->GetRectangle())) {
            m_EggController.EggListPopAtIndex(i);
        }

        if(egg->GetRectangle().y > m_Window.GetSize().y) {
            m_EggController.EggListPopAtIndex(i);
        }
    }

    
}   

void SceneGameplay::Render() {
    m_Window.ClearBackground(raylib::Color(172, 204, 228));

    m_GameLogo.Draw(raylib::Vector2(m_LogoPosition.x - m_GameLogo.width / 2.0f, m_LogoPosition.y - m_GameLogo.height / 2.0f), WHITE);

    m_Player.Render();
    m_EggController.Render();
} 

bool SceneGameplay::GameStarted() {
    return m_Player.Enabled() && m_EggController.Enabled();
}