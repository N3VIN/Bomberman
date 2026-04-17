#pragma once
#include "Components/Component.h"
#include "../../Core/Patterns/Subject.h"

namespace dae {
    class HealthComponent final : public Component, public Subject {
    public:
        explicit HealthComponent(GameObject *gameObject, int lives);

        void Die();
        [[nodiscard]] int GetLives() const;

    private:
        int m_lives;
    };
}
