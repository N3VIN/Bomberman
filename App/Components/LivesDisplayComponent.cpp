#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Components/TextComponent.h"

namespace dae {
    LivesDisplayComponent::LivesDisplayComponent(GameObject *owner, int startingLives)
        : Component(owner)
      , m_textComponent(owner->GetComponent<TextComponent>()) {
        m_textComponent->SetText("Lives: " + std::to_string(startingLives)); // TODO: startingLives is only used to display the initial text. find a way to remove this dependancy.
    }

    void LivesDisplayComponent::OnNotify(GameObject *gameObject, GameEvent event) {
        if (!m_healthComponent) {
            m_healthComponent = gameObject->GetComponent<HealthComponent>();
        }

        if (event == GameEvent::PlayerDied) {
            const int lives = m_healthComponent->GetLives();
            m_textComponent->SetText("Lives: " + std::to_string(lives));
        }
    }
}
