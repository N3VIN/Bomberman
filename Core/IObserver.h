#pragma once
#include <vector>

namespace dae {
    class GameObject;
    class Subject;

    enum class GameEvent {
        PlayerDied,
        PickupPicked
    };

    class IObserver {
    public:
        virtual ~IObserver();
        virtual void OnNotify(GameObject *gameObject, GameEvent event) = 0;

    private:
        friend class Subject;
        std::vector<Subject *> m_subjects{};
    };
}
