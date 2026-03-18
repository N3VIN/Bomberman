#pragma once
#include "Command.h"
#include "GameObject.h"
#include "../Components/HealthComponent.h"

namespace dae {
    class DieCommand final : public GameObjectCommand {
    public:
        explicit DieCommand(GameObject *gameObject)
            : GameObjectCommand(gameObject) {
            m_healthComponent = gameObject->GetComponent<HealthComponent>();
        }

        void Execute() override {
            m_healthComponent->Die();
        }

    private:
        HealthComponent *m_healthComponent{nullptr};
    };
}
