#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime) {
    if (m_activeScene) {
        m_activeScene->Update(deltaTime);
    }
}

void dae::SceneManager::FixedUpdate() {
    if (m_activeScene) {
        m_activeScene->FixedUpdate();
    }
}

void dae::SceneManager::Render() const {
    if (m_activeScene) {
        m_activeScene->Render();
    }
}

// this is temp
dae::Scene &dae::SceneManager::CreateScene() {
    m_scenes.emplace_back(new Scene());
    auto &scene = *m_scenes.back();
    if (!m_activeScene) {
        m_activeScene = &scene;
    }

    return scene;
}

void dae::SceneManager::SetActiveScene(Scene &scene) {
    m_activeScene = &scene;
}
