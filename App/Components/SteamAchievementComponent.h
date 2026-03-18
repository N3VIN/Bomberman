#pragma once
#include "Observer.h"
#include "Components/Component.h"

namespace dae {
    class PickupComponent;

    class SteamAchievementComponent final : public Component, public Observer {
    public:
        explicit SteamAchievementComponent(GameObject *owner);

        void OnNotify(GameObject *gameObject, GameEvent event) override;

        static constexpr int SCORE_TO_WIN{500};

    private:
        PickupComponent *m_pickupComponent{nullptr};
        bool m_achieved{false};
    };
}
