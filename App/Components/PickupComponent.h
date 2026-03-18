#pragma once
#include "Observer.h"
#include "Components/Component.h"

namespace dae {
    class PickupComponent final : public Component, public Subject {
        public:
        explicit PickupComponent(GameObject *gameObject, int score);

        void OnPickup(int value);
        [[nodiscard]] int GetScore() const;

    private:
        int m_score;
    };
}
