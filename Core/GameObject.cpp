#include <string>
#include "GameObject.h"
// #include "ResourceManager.h"
// #include "Renderer.h"
#include "Components/Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime) {
    for (auto &component: m_components) {
        component->Update(deltaTime);
    }
}

void dae::GameObject::Render() const {
    for (const auto &component: m_components) {
        component->Render();
    }
}

void dae::GameObject::SetPosition(const glm::vec2 &position) {
    m_transform.SetPosition(position.x, position.y, 0.0f);
}

glm::vec2 dae::GameObject::GetPosition() const {
    return m_transform.GetPosition();
}

template<typename T, typename... Args>
T *dae::GameObject::AddComponent(Args &&... args) {
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    auto &component = m_components.emplace_back(std::make_unique<T>(this, std::forward<Args>(args)...));
    return static_cast<T *>(component.get());
}

template<typename T>
T *dae::GameObject::GetComponent() const {
    for (auto &component: m_components) {
        if (auto *ptr = dynamic_cast<T *>(component.get())) {
            return ptr;
        }
    }

    return nullptr;
}

template<typename T>
bool dae::GameObject::HasComponent() const {
    for (auto &component: m_components) {
        if (dynamic_cast<T *>(component.get())) {
            return true;
        }
    }

    return false;
}

template<typename T>
void dae::GameObject::RemoveComponent() {
    for (size_t i = m_components.size(); i-- > 0;) {
        if (dynamic_cast<T *>(m_components[i].get())) {
            // assuming that the order for the components inside the gameobject dont matter
            std::swap(m_components[i], m_components.back());
            m_components.pop_back();
            return;
        }
    }
}
