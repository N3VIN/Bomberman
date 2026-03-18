#include "SteamAchievementComponent.h"
#include "PickupComponent.h"
#include "GameObject.h"

#if USE_STEAMWORKS
#pragma warning(push)
#pragma warning(disable:4996)
#include <steam_api.h>
#pragma warning(pop)
#endif

namespace dae {
    SteamAchievementComponent::SteamAchievementComponent(GameObject *owner)
        : Component(owner) {}

    void SteamAchievementComponent::OnNotify(GameObject *gameObject, GameEvent event) {
        if (m_achieved) return;

        if (!m_pickupComponent)
            m_pickupComponent = gameObject->GetComponent<PickupComponent>();

        if (event == GameEvent::PickupPicked && m_pickupComponent->GetScore() >= SCORE_TO_WIN) {
            m_achieved = true;
#if USE_STEAMWORKS
            SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
            SteamUserStats()->StoreStats();
#endif
        }
    }
}
