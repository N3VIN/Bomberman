#include "../Patterns/Subject.h"

namespace dae {
    Subject::~Subject() {
        for (auto* observer : m_observers) {
            std::erase(observer->m_subjects, this);
        }

    }

    void Subject::AddObserver(IObserver *observer) {
        m_observers.push_back(observer);
        observer->m_subjects.emplace_back(this);
    }

    void Subject::RemoveObserver(IObserver *observer) {
        std::erase(m_observers, observer);
        std::erase(observer->m_subjects, this);
    }

    void Subject::Notify(GameObject *gameObject, GameEvent event) const {
        for (auto* observer : m_observers) {
            observer->OnNotify(gameObject, event);
        }
    }
} // dae