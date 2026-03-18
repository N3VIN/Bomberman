#pragma once
#include <vector>

namespace dae {
    class GameObject;

    enum class GameEvent {
        PlayerDied,
        PickupPicked
    };

    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void OnNotify(GameObject *gameObject, GameEvent event) = 0;
    };

    class Subject {
    public:
        void AddObserver(Observer *observer) {
            m_observers.emplace_back(observer);
        }

        void RemoveObserver(Observer *observer) {
            std::erase(m_observers, observer);
        }

    protected:
        void Notify(GameObject *gameObject, GameEvent event) const {
            for (auto *observer: m_observers) {
                observer->OnNotify(gameObject, event);
            }
        }

    private:
        std::vector<Observer *> m_observers{};
    };
}
