#pragma once

#include "IObserver.h"

namespace dae {
    class Subject {
    public:
        virtual ~Subject();
        void AddObserver(IObserver *observer);
        void RemoveObserver(IObserver *observer);

    protected:
        void Notify(GameObject *gameObject, GameEvent event) const;

    private:
        std::vector<IObserver *> m_observers;
    };
} // dae
