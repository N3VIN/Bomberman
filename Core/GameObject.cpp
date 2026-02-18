#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() {}

void dae::GameObject::Render() const {
    const auto &pos = m_transform.GetPosition();
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string &filename) {
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y) {
    m_transform.SetPosition(x, y, 0.0f);
}

template<typename T, typename... Args>
T *dae::GameObject::AddComponent(Args &&... args) {
    auto &component = m_components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
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
            // assuming that the order for the components dont matter
            std::swap(m_components[i], m_components.back());
            m_components.pop_back();
            return;
        }
    }
}
