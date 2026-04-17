#include "IObserver.h"
#include "Subject.h"

dae::IObserver::~IObserver() {
    for (auto* subject : m_subjects) {
        subject->RemoveObserver(this);
    }
}
