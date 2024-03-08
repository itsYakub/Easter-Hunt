#pragma once

#include <memory>

#include "Scene.hpp"

class SceneMenager {
private:
    std::unique_ptr<Scene> m_CurrentScene;

public:
    SceneMenager();
    SceneMenager(Scene* scene);
    void LoadScene(Scene* scene);
    void Update();
    void Render();
};