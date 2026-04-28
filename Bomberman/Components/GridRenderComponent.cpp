#include "GridRenderComponent.h"
#include "../../Core/Components/RenderComponent.h"
#include "../../Core/SceneGraph/GameObject.h"

namespace dae {
    GridRenderComponent::GridRenderComponent(GameObject *parent, const std::string &texturePath, const SDL_Rect &sourceRect, float scale)
        : Component(parent) {
        if (!parent->HasComponent<RenderComponent>()) {
            parent->AddComponent<RenderComponent>();
        }

        m_renderComponent = parent->GetComponent<RenderComponent>();
        m_renderComponent->SetTexture(texturePath);
        m_renderComponent->SetSourceRect(sourceRect);
        m_renderComponent->SetScale(scale);
    }
}
