#include "EggController.hpp"

#include <array>
#include <vector>
#include <memory>

#include "raylib-cpp.hpp"

#include "Egg.hpp"
#include "Timer.hpp"

EggController::EggController(Display& display) :
    m_Display(display), 
    m_EggTexture("../res/txt/EasterHunt_Egg.png"),
    m_ColorList(),
    m_EggList(0), 
    m_EggSpawnDelayTime(2.0f), 
    m_EggSpawnDelayTimer(5.0f) { }

void EggController::Update() {
    if(!m_Enabled) {
        return;
    }

    m_EggSpawnDelayTimer.Process(m_Display.GetFrameTime());

    if(m_EggSpawnDelayTimer.Finished()) {
        m_EggList.push_back(std::make_unique<Egg>(m_Display, m_EggTexture, m_ColorList.GetRandomColor(), GetRandomValue(128, m_Display.GetSize().x - 128)));
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

bool EggController::Enabled() {
    return m_Enabled;
}

void EggController::Enable() {
    m_Enabled = true;
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