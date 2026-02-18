#include <string>
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"

#define INSTANTIATE_COMPONENT(T) \
    template T* GameObject::AddComponent<T>(); \
    template T* GameObject::GetComponent<T>() const; \
    template bool GameObject::HasComponent<T>() const; \
    template void GameObject::RemoveComponent<T>();

namespace dae {
    INSTANTIATE_COMPONENT(RenderComponent)
    INSTANTIATE_COMPONENT(TextComponent)
    INSTANTIATE_COMPONENT(FPSComponent)
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime) {
    for (auto &[type, component]: m_components) {
        component->Update(deltaTime);
    }
}

void dae::GameObject::FixedUpdate() {
    for (auto &[type, component]: m_components) {
        component->FixedUpdate();
    }
}

void dae::GameObject::Render() const {
    for (const auto &[type, component]: m_components) {
        component->Render();
    }
}

void dae::GameObject::SetPosition(const glm::vec2 &position) {
    m_transform.SetPosition(position.x, position.y, 0.0f);
}

glm::vec2 dae::GameObject::GetPosition() const {
    return m_transform.GetPosition();
}

template<typename T>
T *dae::GameObject::AddComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    auto [it, inserted] = m_components.emplace(GetTypeId<T>(), std::make_unique<T>(this));
    return static_cast<T *>(it->second.get());
}

template<typename T>
T *dae::GameObject::GetComponent() const {
    auto it = m_components.find(GetTypeId<T>());
    return it != m_components.end() ? static_cast<T *>(it->second.get()) : nullptr;
}

template<typename T>
bool dae::GameObject::HasComponent() const {
    return m_components.contains(GetTypeId<T>());
}

template<typename T>
void dae::GameObject::RemoveComponent() {
    m_components.erase(GetTypeId<T>());
}

