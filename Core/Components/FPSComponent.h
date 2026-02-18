#pragma once
#include "Component.h"

namespace dae {
    constexpr float UPDATE_INTERVAL = 1.0f;

    class FPSComponent final : public Component {
    public:
        explicit FPSComponent(GameObject *owner);

        void Update(float deltaTime) override;

    private:
        int m_frameCount{};
        float m_elapsedTime{};
    };
} // dae
