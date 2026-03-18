#pragma once
#include "Components/Component.h"
#include "Observer.h"

namespace dae {
    class HealthComponent final : public Component, public Subject {
    public:
        explicit HealthComponent(GameObject *gameObject, int lives = 3);

        void Die();
        [[nodiscard]] int GetLives() const { return m_lives; }

    private:
        int m_lives;
    };
}
