#pragma once
#include "Components/Component.h"
#include "Observer.h"

namespace dae {
    class TextComponent;

    class LivesDisplayComponent final : public Component, public Observer {
    public:
        explicit LivesDisplayComponent(GameObject *owner, int startingLives = 3);

        void OnNotify(GameObject *gameObject, GameEvent event) override;

    private:
        int m_lives;
        TextComponent *m_text;
    };
}
