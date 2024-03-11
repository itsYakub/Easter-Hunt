#include "SceneGameplay.hpp"

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"

SceneGameplay::SceneGameplay(Display& display, SceneMenager& sceneMenager) : 
    m_Display(display),
    m_SceneMenager(sceneMenager),
    m_Player(display),
    m_EggController(display),
    m_GameLogo("../res/txt/EasterHunt_Logo.png"),
    m_LogoPosition(0.0f, 0.0f),
    m_TooltipText(GetFontDefault(), "- - - Press SPACE to start - - -", 32, 2, BLACK),
    m_TooltipPosition(raylib::Vector2(m_Display.GetSize().x / 2.0f - m_TooltipText.MeasureEx().x / 2.0, 512.0f)),
    m_Background(display) {
        m_GameLogo.SetFilter(TEXTURE_FILTER_BILINEAR);
        m_LogoPosition = raylib::Vector2(m_Display.GetSize().x / 2.0f, 128.0f);
}

void SceneGameplay::Update() {
    if(IsKeyPressed(KEY_SPACE) && (!GameStarted())) {
        m_Player.Enable();
        m_Player.OnEnable();

        m_EggController.Enable();
    }

    else if(GameStarted()) {
        m_LogoPosition.y = Lerp(m_LogoPosition.y, -m_GameLogo.height, 0.8f * GetFrameTime());
        m_TooltipPosition.y = Lerp(m_TooltipPosition.y, m_Display.GetSize().y + m_TooltipText.MeasureEx().y, GetFrameTime());
    }

    m_Player.Update();
    m_EggController.Update();

    for(int i = 0; i < m_EggController.GetEggList().size(); i++) {
        auto egg = m_EggController.GetEggList().at(i).get();

        if(m_Player.GetRectangle().CheckCollision(egg->GetRectangle())) {
            m_EggController.EggListPopAtIndex(i);
            m_Player.IncrementScore();
        }

        if(egg->GetRectangle().y > m_Display.GetSize().y) {
            m_EggController.EggListPopAtIndex(i);
            m_Player.DecrementLives();
        }
    }

    m_Background.Update();
}   

void SceneGameplay::Render() {
    ClearBackground(raylib::Color(172, 204, 228));

    m_Background.Render();
    m_GameLogo.Draw(raylib::Vector2(m_LogoPosition.x - m_GameLogo.width / 2.0f, m_LogoPosition.y - m_GameLogo.height / 2.0f), WHITE);
    m_TooltipText.Draw(m_TooltipPosition);

    m_Player.Render();
    m_EggController.Render();
} 

bool SceneGameplay::GameStarted() {
    return m_Player.Enabled() && m_EggController.Enabled();
}