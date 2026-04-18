#include "GridRenderComponent.h"
#include "../TileConfig.h"
#include "../../Core/Components/RenderComponent.h"
#include "../../Core/SceneGraph/GameObject.h"

namespace dae {
    GridRenderComponent::GridRenderComponent(GameObject *parent)
        : Component(parent) {
        if (!parent->HasComponent<RenderComponent>()) {
            parent->AddComponent<RenderComponent>();
        }

        m_renderComponent = parent->GetComponent<RenderComponent>();
        m_renderComponent->SetTexture(TileConfig::BackgroundPath);
        m_renderComponent->SetSourceRect(TileConfig::BackgroundSourceRect);
        m_renderComponent->SetScale(TileConfig::Scale);
    }
}
