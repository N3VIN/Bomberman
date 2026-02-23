#include "GameObject.h"
#include "Components/RenderComponent.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime) {
    for (auto &component: m_components) {
        component->Update(deltaTime);
    }
}

void dae::GameObject::FixedUpdate() {
    for (auto &component: m_components) {
        component->FixedUpdate();
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
