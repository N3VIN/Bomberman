#pragma once

namespace dae {
    class GameObject;

    class Component {
    public:
        explicit Component(GameObject *parent)
            : m_parent(parent) {}

        virtual ~Component() = default;
        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;
        Component(Component &&) = delete;
        Component &operator=(Component &&) = delete;

        virtual void Update(float /*deltaTime*/) {}
        virtual void FixedUpdate() {}
        virtual void Render() const {}

        GameObject *GetParent() const { return m_parent; }

    private:
        GameObject *m_parent = nullptr;
    };
} // dae
