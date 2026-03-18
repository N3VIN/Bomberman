#pragma once
#include "Command.h"
#include "GameObject.h"
#include "../Components/HealthComponent.h"

namespace dae {
    class DieCommand final : public GameObjectCommand {
    public:
        explicit DieCommand(GameObject *gameObject)
            : GameObjectCommand(gameObject) {}

        void Execute() override {
            GetGameObject()->GetComponent<HealthComponent>()->Die();
        }
    };
}
