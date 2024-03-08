#include "EggController.hpp"

#include <array>
#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

#include "Egg.hpp"
#include "Timer.hpp"

EggController::EggController(raylib::Window& window) :
    m_Window(window), 
    m_EggTexture("../res/txt/EasterHunt_Egg.png"),
    m_EggColorList( { raylib::Color(108, 86, 113), raylib::Color(176, 169, 228), raylib::Color(249, 130, 132), raylib::Color(254, 170, 228), raylib::Color(172, 204, 228), raylib::Color(179, 227, 218), raylib::Color(176, 235, 147), raylib::Color(233, 245, 157) } ),
    m_EggList(0), 
    m_EggSpawnDelayTime(2.4f), 
    m_EggSpawnDelayTimer(6.4f) { }

void EggController::Update() {
    m_EggSpawnDelayTimer.Process(m_Window.GetFrameTime());

    if(m_EggSpawnDelayTimer.Finished()) {
        m_EggList.push_back(std::make_unique<Egg>(m_Window, m_EggTexture, m_EggColorList.at(GetRandomValue(0, m_EggColorList.size() - 1)), GetRandomValue(1, m_Window.GetSize().y / 100.0f - 1) * 100));
        m_EggSpawnDelayTimer.Restart(m_EggSpawnDelayTime);
    }

    for(int i = 0; i < m_EggList.size(); i++) {
        m_EggList.at(i)->Update();
    }
}

void EggController::Render() {
    for(auto& i : m_EggList) {
        i->Render();
    }
}

const std::vector<std::unique_ptr<Egg>>& EggController::GetEggList() const {
    return m_EggList;
}

// TODO(Yakub):
// Maybe add some functions that erases the eggs based on their memory address, 
// so you don't need to use indexing anymore.
// For now though, let's stay with this solution.
void EggController::EggListPopAtIndex(int index) {
    m_EggList.erase(m_EggList.begin() + index);
}