#include "RenderComponent.h"

#include <glm/trigonometric.hpp>
#include "../SceneGraph/GameObject.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/ResourceManager.h"
#include "../Renderer/Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject *parent)
    : Component(parent) {}

void dae::RenderComponent::Update(float /*deltaTime*/) {}

void dae::RenderComponent::Render() const {
    if (!m_texture) {
        return;
    }

    const auto pos = GetParent()->GetWorldPosition();
    if (m_hasSrcRect) {
        const float destWidth = static_cast<float>(m_srcRect.w) * m_scale;
        const float destHeight = static_cast<float>(m_srcRect.h) * m_scale;
        Renderer::GetInstance().RenderTexture(*m_texture, m_srcRect, pos.x, pos.y, destWidth, destHeight);
        return;
    }

    if (m_scale != 1.f) {
        const glm::vec2 size = m_texture->GetSize();
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, size.x * m_scale, size.y * m_scale);
        return;
    }

    const auto rotation = glm::degrees(GetParent()->GetWorldRotation());
    Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, rotation);
}

void dae::RenderComponent::SetTexture(const std::string &filename) {
    m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture) {
    m_texture = std::move(texture);
}

void dae::RenderComponent::SetSourceRect(int x, int y, int w, int h) {
    m_srcRect = {x, y, w, h};
    m_hasSrcRect = true;
}

void dae::RenderComponent::SetSourceRect(const SDL_Rect &rect) {
    m_srcRect = rect;
    m_hasSrcRect = true;
}

void dae::RenderComponent::ClearSourceRect() {
    m_srcRect = {0, 0, 0, 0};
    m_hasSrcRect = false;
}

void dae::RenderComponent::SetScale(float scale) {
    m_scale = scale;
}
