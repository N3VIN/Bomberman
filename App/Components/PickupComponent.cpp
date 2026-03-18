#include "PickupComponent.h"

namespace dae {
    PickupComponent::PickupComponent(GameObject *gameObject, int score)
        : Component(gameObject)
      , m_score(score) {}

    void PickupComponent::OnPickup(int value) {
        m_score += value;
        Notify(GetParent(), GameEvent::PickupPicked);
    }

    int PickupComponent::GetScore() const {
        return m_score;
    }
}
