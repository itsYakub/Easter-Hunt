#pragma once

#include <array>
#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

#include "Egg.hpp"
#include "Timer.hpp"
#include "Display.hpp"
#include "Resources.hpp"
#include "ColorList.hpp"

class EggController {
private:
    Display& m_Display;
    Resources& m_Resources;

    raylib::Texture2D& m_EggTexture;
    ColorList m_ColorList;

    std::vector<std::unique_ptr<Egg>> m_EggList;

    float m_EggSpawnDelayTime;
    Timer m_EggSpawnDelayTimer;

    bool m_Enabled;

public:
    EggController(Display& display, Resources& resources);

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

    // TODO(Yakub):
    // Add some functionality for decreasing the time delay between spawning the eggs, to make the game more difficult over time
    // Maybe base it on the current player score, or on the current game time
};
