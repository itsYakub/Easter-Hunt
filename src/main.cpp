// External links:
// > Color Palette: https://lospec.com/palette-list/vanilla-milkshake

#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

class Timer {
private:
    float m_Time;

public:
    Timer(float time) : m_Time(time) { }
    void Process(float deltaTime) { m_Time -= deltaTime; }
    void Restart(float time) { m_Time = time; }
    bool Finished() { return m_Time <= 0.0f; }
};

class Egg {
private:
    raylib::Window& m_Window;

    raylib::Texture2D& m_Texture;
    raylib::Rectangle m_BoundingRect;
    raylib::Color m_Color;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

public:
    Egg(raylib::Window& window, raylib::Texture2D& texture, raylib::Color color, float position) : 
        m_Window(window),
        m_Texture(texture),
        m_BoundingRect(position, -128.0f, m_Texture.width, m_Texture.height),
        m_Color(color),
        m_Gravity(0.0f, 1.6f),
        m_Velocity(0.0f, 0.0f) { 
            m_Texture.SetFilter(TEXTURE_FILTER_ANISOTROPIC_16X);
        }

    void Update() {
        m_Velocity += m_Gravity * m_Window.GetFrameTime();
        m_BoundingRect.x += m_Velocity.x;
        m_BoundingRect.y += m_Velocity.y;
    }    

    void Render() {
        m_Texture.Draw(
            raylib::Rectangle(0.0f, 0.0f, m_Texture.width, m_Texture.height), 
            raylib::Rectangle(m_BoundingRect.x, m_BoundingRect.y, m_Texture.width, m_Texture.height), 
            raylib::Vector2::Zero(), 
            0.0f, 
            m_Color
        );    
    }

    raylib::Rectangle GetRectangle() const {
        return m_BoundingRect;
    }
};

class Player {
private:
    raylib::Window& m_Window;

    raylib::Texture2D m_Texture;
    raylib::Rectangle m_BoundingRect;

    const raylib::Vector2 m_Gravity;
    raylib::Vector2 m_Velocity;

    float m_Rotation;

    int m_Score;
    int m_Lives;

    bool m_Enabled;

public:
    Player(raylib::Window& window) : 
        m_Window(window),
        m_Texture("../res/txt/EasterHunt_Bunny.png"),
        m_BoundingRect(m_Window.GetSize().x / 2.0f - m_Texture.width / 2.0f, m_Window.GetSize().y / 2.0f - m_Texture.height / 2.0f, m_Texture.width, m_Texture.height),
        m_Gravity(0.0f, 9.81f * 2),
        m_Velocity(0.0f, 0.0f),
        m_Rotation(0.0f),
        m_Score(0),
        m_Lives(3),
        m_Enabled(false) { 
            m_Texture.SetFilter(TEXTURE_FILTER_ANISOTROPIC_16X);
        }

    void Update() {
        if(!m_Enabled) {
            if(raylib::Keyboard::IsKeyPressed(KEY_SPACE)) {
                m_Enabled = true;
                m_Velocity.y = -4.0f;
            }

            return;
        } 

        if(m_BoundingRect.x + m_BoundingRect.width < 0.0f) {
            m_BoundingRect.x = m_Window.GetSize().x + m_BoundingRect.width;
        } else if(m_BoundingRect.x - m_BoundingRect.width > m_Window.GetSize().x) {
            m_BoundingRect.x = 0.0f - m_BoundingRect.width;
        }

        if(m_BoundingRect.y + m_BoundingRect.height >= m_Window.GetSize().y) {
            m_BoundingRect.y = m_Window.GetSize().y - m_BoundingRect.height;
            m_Velocity.y = m_Velocity.y / 1.5f * -1.0f;
        }

        if(raylib::Keyboard::IsKeyDown(KEY_SPACE) && m_BoundingRect.y >= 0.0f) {
            m_Velocity.y -= m_Gravity.y * 2.0f * GetFrameTime();
        }

        m_Velocity.x = Lerp(m_Velocity.x, 8.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Window.GetFrameTime());
        m_Rotation = Lerp(m_Rotation, 30.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Window.GetFrameTime());

        m_Velocity += m_Gravity * m_Window.GetFrameTime();
        m_BoundingRect.x += m_Velocity.x;
        m_BoundingRect.y += m_Velocity.y;
    }

    void Render() {
        m_Texture.Draw(
            raylib::Rectangle(0.0f, 0.0f, m_Texture.width, m_Texture.height), 
            raylib::Rectangle(m_BoundingRect.x + m_Texture.width / 2.0f, m_BoundingRect.y + m_Texture.height / 2.0f, m_Texture.width, m_Texture.height), 
            raylib::Vector2(m_Texture.width, m_Texture.height) / 2.0f, 
            m_Rotation, 
            WHITE
        );
    }

    raylib::Rectangle GetRectangle() const {
        return m_BoundingRect;
    }

    void IncrementScore() {
        m_Score++;
    }

    void DecrementLives() {
        m_Lives--;
    }

    int GetScore() const {
        return m_Score;
    }

    int GetLives() const {
        return m_Lives;
    }
};

class EggController {
private:
    raylib::Window& m_Window;
    raylib::Texture2D m_EggTexture;
    const std::array<raylib::Color, 8> m_EggColorList;

    std::vector<std::unique_ptr<Egg>> m_EggList;

    const float m_EggSpawnDelayTime;
    Timer m_EggSpawnDelayTimer;

public:
    EggController(raylib::Window& window) :
        m_Window(window), 
        m_EggTexture("../res/txt/EasterHunt_Egg.png"),
        m_EggColorList( { raylib::Color(108, 86, 113), raylib::Color(176, 169, 228), raylib::Color(249, 130, 132), raylib::Color(254, 170, 228), raylib::Color(172, 204, 228), raylib::Color(179, 227, 218), raylib::Color(176, 235, 147), raylib::Color(233, 245, 157) } ),
        m_EggList(0), 
        m_EggSpawnDelayTime(2.4f), 
        m_EggSpawnDelayTimer(6.4f) { }

    void Update() {
        m_EggSpawnDelayTimer.Process(m_Window.GetFrameTime());

        if(m_EggSpawnDelayTimer.Finished()) {
            m_EggList.push_back(std::make_unique<Egg>(m_Window, m_EggTexture, m_EggColorList.at(GetRandomValue(0, m_EggColorList.size() - 1)), GetRandomValue(1, m_Window.GetSize().y / 100.0f - 1) * 100));
            m_EggSpawnDelayTimer.Restart(m_EggSpawnDelayTime);
        }

        for(int i = 0; i < m_EggList.size(); i++) {
            m_EggList.at(i)->Update();
        }
    }

    void Render() {
        for(auto& i : m_EggList) {
            i->Render();
        }
    }

    const auto& GetEggList() const {
        return m_EggList;
    }

    // TODO(Yakub):
    // Maybe add some functions that erases the eggs based on their memory address, 
    // so you don't need to use indexing anymore.
    // For now though, let's stay with this solution.
    void EggListPopAtIndex(int index) {
        m_EggList.erase(m_EggList.begin() + index);
    }
};

int main(int argc, char** argv) {
    raylib::Window window(786, 786, "Raylib 5.0.0 - Easter Hunt 1.0.0", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    
    Player player(window);
    EggController eggController(window);

    while(!WindowShouldClose()) {
        player.Update();
        eggController.Update();

        for(int i = 0; i < eggController.GetEggList().size(); i++) {
            auto egg = eggController.GetEggList().at(i).get();

            if(player.GetRectangle().CheckCollision(egg->GetRectangle())) {
                eggController.EggListPopAtIndex(i);
            }

            if(egg->GetRectangle().y > window.GetSize().y) {
                eggController.EggListPopAtIndex(i);
            }
        }
 
        window.BeginDrawing().ClearBackground(raylib::Color(172, 204, 228));

        player.Render();
        eggController.Render();

        window.EndDrawing();
    }

    return 0;
}
