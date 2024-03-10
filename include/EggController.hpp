#pragma once

#include <array>
#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

#include "Egg.hpp"
#include "Timer.hpp"
#include "Display.hpp"

class EggController {
private:
    Display& m_Display;
    raylib::Texture2D m_EggTexture;
    const std::array<raylib::Color, 8> m_EggColorList;

    std::vector<std::unique_ptr<Egg>> m_EggList;

    const float m_EggSpawnDelayTime;
    Timer m_EggSpawnDelayTimer;

    bool m_Enabled;

public:
    EggController(Display& display);

    void Update();
    void Render();

    bool Enabled();
    void Enable();

    const std::vector<std::unique_ptr<Egg>>& GetEggList() const;

    // TODO(Yakub):
    // Maybe add some functions that erases the eggs based on their memory address, 
    // so you don't need to use indexing anymore.
    // For now though, let's stay with this solution.
    void EggListPopAtIndex(int index);
};
