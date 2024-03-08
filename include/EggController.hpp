#pragma once

#include <array>
#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

#include "Egg.hpp"
#include "Timer.hpp"

class EggController {
private:
    raylib::Window& m_Window;
    raylib::Texture2D m_EggTexture;
    const std::array<raylib::Color, 8> m_EggColorList;

    std::vector<std::unique_ptr<Egg>> m_EggList;

    const float m_EggSpawnDelayTime;
    Timer m_EggSpawnDelayTimer;

public:
    EggController(raylib::Window& window);
    void Update();
    void Render();

    const std::vector<std::unique_ptr<Egg>>& GetEggList() const;

    // TODO(Yakub):
    // Maybe add some functions that erases the eggs based on their memory address, 
    // so you don't need to use indexing anymore.
    // For now though, let's stay with this solution.
    void EggListPopAtIndex(int index);
};
