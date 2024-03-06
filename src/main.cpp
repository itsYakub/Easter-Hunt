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

    const raylib::Vector2 m_Gravity;

    raylib::Vector2 m_Position;
    raylib::Vector2 m_Size;
    raylib::Vector2 m_Velocity;

public:
    Egg(raylib::Window& window, float position) : 
        m_Window(window),
        m_Gravity(0.0f, 1.6f),
        m_Position(position, -128.0f),
        m_Size(16.0f, 16.0f),
        m_Velocity(0.0f, 0.0f) { }

    void Update() {
        m_Velocity += m_Gravity * m_Window.GetFrameTime();
        m_Position += m_Velocity;
    }    

    void Render() {
        DrawCircleV(m_Position, 16.0f, WHITE);
    }

    raylib::Vector2 GetPosition() const {
        return m_Position;
    }

    raylib::Vector2 GetSize() const {
        return m_Size;
    }

    raylib::Rectangle GetCollider() const {
        return raylib::Rectangle(m_Position, m_Size);
    }
};

class Player {
private:
    raylib::Window& m_Window;

    const raylib::Vector2 m_Gravity;

    raylib::Vector2 m_Position;
    raylib::Vector2 m_Size;
    raylib::Vector2 m_Velocity;

    int m_Score;
    int m_Lives;

    bool m_Enabled;

public:
    Player(raylib::Window& window) : 
        m_Window(window),
        m_Gravity(0.0f, 9.81f * 2),
        m_Position(0.0f, 0.0f),
        m_Size(64.0f, 64.0f),
        m_Velocity(0.0f, 0.0f),
        m_Score(0),
        m_Lives(3),
        m_Enabled(false) {
            m_Position = m_Window.GetSize() / 2.0f - m_Size / 2.0f;
        }

    void Update() {
        if(!m_Enabled) {
            if(raylib::Keyboard::IsKeyPressed(KEY_SPACE)) {
                m_Enabled = true;
                m_Velocity.y = -4.0f;
            }

            return;
        } 

        if(m_Position.x + m_Size.x < 0.0f) {
            m_Position.x = m_Window.GetSize().x;
        } else if(m_Position.x > m_Window.GetSize().x) {
            m_Position.x = 0.0f - m_Size.x;
        }

        if(m_Position.y + m_Size.y >= m_Window.GetSize().y) {
            m_Position.y = m_Window.GetSize().y - m_Size.y;
            m_Velocity.y = m_Velocity.y / 1.5f * -1.0f;
        }

        if(raylib::Keyboard::IsKeyDown(KEY_SPACE) && m_Position.y + m_Size.y >= 0.0f) {
            m_Velocity.y -= m_Gravity.y * 2.0f * GetFrameTime();
        }

        m_Velocity.x = Lerp(m_Velocity.x, 8.0f * (raylib::Keyboard::IsKeyDown(KEY_D) - raylib::Keyboard::IsKeyDown(KEY_A)), 2.0f * m_Window.GetFrameTime());

        m_Velocity += m_Gravity * m_Window.GetFrameTime();
        m_Position += m_Velocity;
    }

    void Render() {
        raylib::Rectangle rect(m_Position, m_Size);
        rect.Draw(RED);

        DrawText(TextFormat("Score: %i\nLives: %i", m_Score, m_Lives), 0, 0, 16, RAYWHITE);
    }

    raylib::Vector2 GetPosition() const {
        return m_Position;
    }

    raylib::Vector2 GetSize() const {
        return m_Size;
    }

    raylib::Rectangle GetCollider() const {
        return raylib::Rectangle(m_Position, m_Size);
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

    std::vector<std::unique_ptr<Egg>> m_EggList;

    const float m_EggSpawnBoundOffset;

    const float m_EggSpawnDelayTime;
    Timer m_EggSpawnDelayTimer;

public:
    EggController(raylib::Window& window) :
        m_Window(window), m_EggList(0), m_EggSpawnBoundOffset(128.0f), m_EggSpawnDelayTime(2.4f), m_EggSpawnDelayTimer(6.4f) { }

    void Update() {
        m_EggSpawnDelayTimer.Process(m_Window.GetFrameTime());

        if(m_EggSpawnDelayTimer.Finished()) {
            // ATTENTION: This code can work badly in the future
            // The values from 1 to 9 were based on the current window width: 1024
            m_EggList.push_back(std::make_unique<Egg>(m_Window, GetRandomValue(1, 9) * 100));
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

    void CheckEggCatch(int index, Player& player) {
        m_EggList.erase(m_EggList.begin() + index);
        player.IncrementScore();
        
        TraceLog(LOG_INFO, TextFormat("Egg %i was caught", index));
    }

    void CheckEggCrash(int index, Player& player) {
        m_EggList.erase(m_EggList.begin() + index);
        player.DecrementLives();

        TraceLog(LOG_INFO, TextFormat("Egg %i has crashed", index));
    }
};

int main(int argc, char** argv) {
    raylib::Window window(1024, 1024, "Raylib 5.0.0 - Easter Hunt 1.0.0", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    
    Player player(window);
    EggController eggController(window);

    while(!WindowShouldClose()) {
        player.Update();
        eggController.Update();

        for(int i = 0; i < eggController.GetEggList().size(); i++) {
            if(player.GetCollider().CheckCollision(eggController.GetEggList().at(i)->GetCollider())) {
                eggController.CheckEggCatch(i, player);
            }

            if(eggController.GetEggList().at(i)->GetPosition().y > window.GetSize().y) {
                eggController.CheckEggCrash(i, player);
            }
        }
 
        window.BeginDrawing().ClearBackground(BLACK);

        player.Render();
        eggController.Render();

        window.EndDrawing();
    }

    return 0;
}