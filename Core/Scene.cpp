#include <algorithm>
#include <cassert>
#include "Scene.h"

using namespace dae;


void Scene::Add(std::unique_ptr<GameObject> object) {
    assert(object != nullptr && "Cannot add a null GameObject to the scene.");
    m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject &object) {
    for (auto &go: m_objects) {
        if (go.get() == &object) {
            m_markedObjects.emplace_back(std::move(go));
        }
    }
}

void Scene::RemoveAll() {
    m_objects.clear();
}

void Scene::Update(float deltaTime) {
    for (auto &object: m_objects) {
        if (object.get() != nullptr) {
            object->Update(deltaTime);
        }
    }

    DeleteMarkedObjects();
}

void Scene::FixedUpdate() {
    for (auto &object: m_objects) {
        if (object.get() != nullptr) {
            object->FixedUpdate();
        }
    }
}

void Scene::Render() const {
    for (const auto &object: m_objects) {
        if (object.get() != nullptr) {
            object->Render();
        }
    }
}

void Scene::DeleteMarkedObjects() {
    std::erase(m_objects, nullptr);
    m_markedObjects.clear();
}
