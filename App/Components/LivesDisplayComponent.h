#pragma once
#include "Components/Component.h"
#include "Observer.h"

namespace dae {
    class TextComponent;
    class HealthComponent;

    class LivesDisplayComponent final : public Component, public Observer {
    public:
        explicit LivesDisplayComponent(GameObject *owner, int startingLives);

        void OnNotify(GameObject *gameObject, GameEvent event) override;

    private:
        TextComponent *m_textComponent;
        HealthComponent *m_healthComponent{nullptr};
    };
}
