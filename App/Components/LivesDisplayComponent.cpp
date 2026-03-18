#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include "Components/TextComponent.h"

namespace dae {
    LivesDisplayComponent::LivesDisplayComponent(GameObject *owner, int startingLives)
        : Component(owner)
      , m_lives(startingLives)
      , m_text(owner->GetComponent<TextComponent>()) {
        m_text->SetText("Lives: " + std::to_string(m_lives));
    }

    void LivesDisplayComponent::OnNotify(GameObject * /*gameObject*/, GameEvent event) {
        if (event == GameEvent::PlayerDied) {
            if (m_lives > 0)
                --m_lives;
            m_text->SetText("Lives: " + std::to_string(m_lives));
        }
    }
}
