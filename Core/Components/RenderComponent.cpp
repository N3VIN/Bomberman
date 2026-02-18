#include "RenderComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(GameObject *parent)
    : Component(parent) {}

void dae::RenderComponent::Update(float /*deltaTime*/) {}

void dae::RenderComponent::Render() const {
    const auto &pos = m_parent->GetPosition();
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::RenderComponent::SetTexture(const std::string &filename) {
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
