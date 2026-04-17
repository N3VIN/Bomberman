#include "RenderComponent.h"

#include <glm/trigonometric.hpp>
#include "../SceneGraph/GameObject.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/ResourceManager.h"

dae::RenderComponent::RenderComponent(GameObject *parent)
    : Component(parent) {}

void dae::RenderComponent::Update(float /*deltaTime*/) {}

void dae::RenderComponent::Render() const {
    if (!m_texture) return;
    const auto pos = GetParent()->GetWorldPosition();
    const auto rot = glm::degrees(GetParent()->GetWorldRotation());
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, rot);
}

void dae::RenderComponent::SetTexture(const std::string &filename) {
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture) {
    m_texture = std::move(texture);
}
