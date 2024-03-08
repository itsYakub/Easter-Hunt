#include "SceneMenager.hpp"

#include <memory>

#include "Scene.hpp"

SceneMenager::SceneMenager() : m_CurrentScene(nullptr) { }
SceneMenager::SceneMenager(Scene* scene) : m_CurrentScene(scene) { }

void SceneMenager::LoadScene(Scene* scene) {
    if(!m_CurrentScene.get()) {
        m_CurrentScene.release();
    }

    m_CurrentScene = std::unique_ptr<Scene>(scene);
}

void SceneMenager::Update() {
    m_CurrentScene.get()->Update();
}

void SceneMenager::Render() {
    m_CurrentScene.get()->Render();
}