#include "HealthComponent.h"
#include "../../Core/SceneGraph/GameObject.h"

namespace dae {
    HealthComponent::HealthComponent(GameObject *gameObject, int lives)
        : Component(gameObject)
      , m_lives(lives) {}

    void HealthComponent::Die() {
        if (m_lives > 0) {
            --m_lives;
            Notify(GetParent(), GameEvent::PlayerDied);
        }
    }

    int HealthComponent::GetLives() const {
        return m_lives;
    }
}
