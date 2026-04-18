#pragma once
#include "HealthComponent.h"
#include "Components/Component.h"

namespace dae {
    class TextComponent;
    class HealthComponent;

    class LivesDisplayComponent final : public Component {
    public:
        ~LivesDisplayComponent() override;
        explicit LivesDisplayComponent(GameObject *owner, HealthComponent* healthComponent);

    private:
        TextComponent *m_textComponent;
        HealthComponent *m_healthComponent{nullptr};
        DelegateHandle m_lambdaHandle;
        DelegateHandle m_memberHandle;

        void OnLifeChanged(int lives) const;
    };
}
