#pragma once

namespace dae {
    class GameObject;

    using TypeId = void(*)(); // to avoid RTTI

    template<typename T>
    static void TypeIdHelper() {}

    template<typename T>
    constexpr TypeId GetTypeId() { return &TypeIdHelper<T>; }

    class Component {
    public:
        explicit Component(GameObject* parent) : m_parent(parent) {}
        virtual ~Component() = default;
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
        Component(Component&&) = delete;
        Component& operator=(Component&&) = delete;

        virtual void Update(float /*deltaTime*/) {}
        virtual void FixedUpdate() {}
        virtual void Render() const {}

        // TODO: SendMessage virtual function

    protected:
        GameObject *m_parent = nullptr;
    };
} // dae
