#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

namespace dae {
    FPSComponent::FPSComponent(GameObject *owner)
        : Component(owner) {}

    void FPSComponent::Update(float deltaTime) {
        ++m_frameCount;
        m_elapsedTime += deltaTime;

        if (m_elapsedTime >= UPDATE_INTERVAL) {
            const auto fps = m_frameCount;
            m_parent->GetComponent<TextComponent>()->SetText(std::to_string(fps) + " FPS");
            m_frameCount = 0;
            m_elapsedTime -= UPDATE_INTERVAL;
        }
    }
}
