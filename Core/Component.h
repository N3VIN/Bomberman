#pragma once

namespace dae {
    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
        virtual void FixedUpdate() = 0;

    protected:
        GameObject *m_parent = nullptr;
    };
} // dae
