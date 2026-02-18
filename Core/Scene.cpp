#include <algorithm>
#include <cassert>
#include "Scene.h"

using namespace dae;

GameObjectHandle Scene::Add(std::unique_ptr<GameObject> object) {
    assert(object != nullptr && "Cannot add a null GameObject to the scene.");

    GameObjectHandle handle = m_nextHandle++;
    const size_t index = m_objects.size();

    object->m_handle = handle;
    m_objects.emplace_back(std::move(object));
    m_handleToIndex[handle] = index;

    return handle;
}

void Scene::Remove(GameObjectHandle handle) {
    auto it = m_handleToIndex.find(handle);
    if (it == m_handleToIndex.end()) return;

    size_t index = it->second;
    size_t lastIndex = m_objects.size() - 1;

    if (index != lastIndex) {
        std::swap(m_objects[index], m_objects[lastIndex]);
        // update the index for swapped objext
        GameObjectHandle swappedHandle = m_objects[index]->m_handle;
        m_handleToIndex[swappedHandle] = index;
    }

    m_objects.pop_back();
    m_handleToIndex.erase(it);
}

void Scene::Remove(const GameObject* object) {
    if (object == nullptr) return;
    Remove(object->GetHandle());
}

void Scene::RemoveAll() {
    m_objects.clear();
    m_handleToIndex.clear();
}

GameObject* Scene::Get(GameObjectHandle handle) const {
    auto it = m_handleToIndex.find(handle);
    if (it == m_handleToIndex.end()) return nullptr;
    return m_objects[it->second].get();
}

void Scene::Update(float deltaTime) {
    for (auto &object: m_objects) {
        object->Update(deltaTime);
    }
}

void Scene::FixedUpdate() {
    for (auto &object: m_objects) {
        object->FixedUpdate();
    }
}

void Scene::Render() const {
    for (const auto &object: m_objects) {
        object->Render();
    }
}
