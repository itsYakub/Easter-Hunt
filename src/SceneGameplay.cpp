#include "SceneGameplay.hpp"

#include "raylib-cpp.hpp"

#include "SceneMenager.hpp"

SceneGameplay::SceneGameplay(Display& display, Resources& resources, SceneMenager& sceneMenager) : 
    m_Display(display),
    m_Resources(resources),
    m_SceneMenager(sceneMenager),
    m_GameLogo(m_Resources.GetTexture("EasterHunt_Logo")),
    m_GameOverScreen(m_Resources.GetTexture("EasterHunt_GameOverScreen")),
    m_Font(m_Resources.GetFont("VarelaRound")),
    m_BackgroundMusic(m_Resources.GetMusic("intro")),
    m_EggCrackSound(m_Resources.GetSound("egg-shell-crush")),
    m_GameplayState(STATE_BEGIN),
    m_Player(display, resources),
    m_EggController(display, resources),
    m_LogoPosition(0.0f, 0.0f),
    m_GameOverScreenPosition(m_Display.GetSize().x / 2.0f, -m_GameOverScreen.GetSize().y / 2.0f),
    m_GameOverCooldownTimer(2.0f),
    m_TooltipText(m_Font, "- - - Press SPACE to start - - -", 32, 2, BLACK),
    m_TooltipPosition(raylib::Vector2(m_Display.GetSize().x / 2.0f - m_TooltipText.MeasureEx().x / 2.0, 512.0f)),
    m_Background(display, resources),
    m_Volume(0.8f),
    m_GameplayTime(0.0f) {
        m_LogoPosition = raylib::Vector2(m_Display.GetSize().x / 2.0f, 128.0f);
        m_BackgroundMusic.SetLooping(true);
        m_BackgroundMusic.Play();
}

void SceneGameplay::Update() {
    m_BackgroundMusic.Update();

    switch(m_GameplayState) {
        case STATE_BEGIN:
            m_BackgroundMusic.SetVolume(m_Volume);

            if(IsKeyPressed(KEY_SPACE) && (!GameStarted())) {
                m_Player.Enable();
                m_Player.OnEnable();

                m_EggController.Enable();

                m_GameplayState = STATE_GAMEPLAY;                
            }

            break;

        case STATE_GAMEPLAY:
            m_Player.Update();
            m_EggController.Update();
            m_Background.Update();

            for(int i = 0; i < static_cast<int>(m_EggController.GetEggList().size()); i++) {
                auto egg = m_EggController.GetEggList().at(i).get();

                if(m_Player.GetRectangle().CheckCollision(egg->GetRectangle())) {
                    m_EggController.EggListPopAtIndex(i);
                    m_Player.IncrementScore();
                }

                if(egg->GetRectangle().y > m_Display.GetSize().y) {
                    m_EggController.EggListPopAtIndex(i);
                    m_Player.DecrementLives();

                    m_EggCrackSound.Play();
                }
            }

            m_LogoPosition.y = Lerp(m_LogoPosition.y, -m_GameLogo.height, 0.8f * GetFrameTime());
            m_TooltipPosition.y = Lerp(m_TooltipPosition.y, m_Display.GetSize().y + m_TooltipText.MeasureEx().y, GetFrameTime());

            if(m_Player.GetLives() <= 0) {
                m_GameplayState = STATE_GAMEOVER;
            }

            m_GameplayTime += m_Display.GetFrameTime();

            break;

        case STATE_GAMEOVER:
            m_Volume = Lerp(m_Volume, 0.2f, m_Display.GetFrameTime());
            m_BackgroundMusic.SetVolume(m_Volume);
            m_GameOverScreenPosition = Vector2Lerp(m_GameOverScreenPosition, m_Display.GetSize() / 2.0f, m_Display.GetFrameTime());

            m_GameOverCooldownTimer.Process(m_Display.GetFrameTime());

            if(raylib::Keyboard::GetKeyPressed() && m_GameOverCooldownTimer.Finished()) {
                m_SceneMenager.LoadScene(new SceneGameplay(m_Display, m_Resources, m_SceneMenager));
            }
            
            break;

        default:

            break;
    }
}   

void SceneGameplay::Render() {
    ClearBackground(raylib::Color(172, 204, 228));
    raylib::Rectangle blackPanel(raylib::Vector2::Zero(), m_Display.GetSize());
    raylib::Text scoreText;
    raylib::Text timeText;

    switch(m_GameplayState) {
        case STATE_BEGIN:
            m_Background.Render();
            m_Player.Render();
            m_EggController.Render();

            m_GameLogo.Draw(raylib::Vector2(m_LogoPosition.x - m_GameLogo.GetSize().x / 2.0f, m_LogoPosition.y - m_GameLogo.GetSize().y / 2.0f));
            m_TooltipText.Draw(m_TooltipPosition);

            break;

        case STATE_GAMEPLAY:
            m_Background.Render();
            m_Player.Render();
            m_EggController.Render();

            m_GameLogo.Draw(raylib::Vector2(m_LogoPosition.x - m_GameLogo.GetSize().x / 2.0f, m_LogoPosition.y - m_GameLogo.GetSize().y / 2.0f));
            m_TooltipText.Draw(m_TooltipPosition);

            break;

        case STATE_GAMEOVER:
            scoreText.SetText(TextFormat("Score: %i", m_Player.GetScore()));
            timeText.SetText(TextFormat("Time: %0.02fs", m_GameplayTime));

            scoreText.SetColor(BLACK);
            scoreText.SetFont(m_Font);
            scoreText.SetFontSize(32);
            scoreText.SetSpacing(2);

            timeText.SetColor(BLACK);
            timeText.SetFont(m_Font);
            timeText.SetFontSize(32);
            timeText.SetSpacing(2);

            m_Background.Render();

            blackPanel.Draw(Fade(BLACK, 0.5f));
            m_GameOverScreen.Draw(
                raylib::Rectangle(raylib::Vector2::Zero(), m_GameOverScreen.GetSize()), 
                raylib::Rectangle(m_GameOverScreenPosition, m_GameOverScreen.GetSize()), 
                raylib::Vector2(m_GameOverScreen.GetSize()) / 2.0f, 
                0.0f, 
                WHITE
            );

            scoreText.Draw(m_GameOverScreenPosition - (scoreText.MeasureEx() / 2.0f));
            timeText.Draw(raylib::Vector2((m_GameOverScreenPosition - (timeText.MeasureEx() / 2.0f)).x, (m_GameOverScreenPosition - (timeText.MeasureEx() / 2.0f)).y + timeText.MeasureEx().y + 2));

            break;

        default:

            break;    
    }
} 

bool SceneGameplay::GameStarted() {
    return m_Player.Enabled() && m_EggController.Enabled();
}