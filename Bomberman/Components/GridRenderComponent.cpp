#include "GridRenderComponent.h"
#include "../SpriteConfig.h"
#include "../../Core/Components/RenderComponent.h"
#include "../../Core/SceneGraph/GameObject.h"

namespace dae {
    GridRenderComponent::GridRenderComponent(GameObject *parent, const SDL_Rect &backgroundSourceRect)
        : Component(parent) {
        if (!parent->HasComponent<RenderComponent>()) {
            parent->AddComponent<RenderComponent>();
        }

        m_renderComponent = parent->GetComponent<RenderComponent>();
        m_renderComponent->SetTexture(SpriteConfig::BackgroundPath);
        m_renderComponent->SetSourceRect(backgroundSourceRect);
        m_renderComponent->SetScale(SpriteConfig::Scale);
    }
}
