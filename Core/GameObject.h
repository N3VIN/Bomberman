#pragma once
#include <string>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include "Transform.h"
#include "Components/Component.h"

namespace dae {
    class Texture2D;
    class Scene;

    using GameObjectHandle = uint32_t;
    constexpr GameObjectHandle INVALID_HANDLE = UINT32_MAX;

    class GameObject final {
        friend class Scene;

    public:
        GameObject() = default;
        ~GameObject();
        GameObject(const GameObject &other) = delete;
        GameObject(GameObject &&other) = delete;
        GameObject &operator=(const GameObject &other) = delete;
        GameObject &operator=(GameObject &&other) = delete;

        void Update(float deltaTime);
        void FixedUpdate();
        void Render() const;

        template<typename T>
        T *AddComponent();

        template<typename T>
        T *GetComponent() const;

        template<typename T>
        [[nodiscard]] bool HasComponent() const;

        template<typename T>
        void RemoveComponent();

        // TODO: SendMessage function

        void SetPosition(const glm::vec2 &position);
        [[nodiscard]] glm::vec2 GetPosition() const;

        [[nodiscard]] GameObjectHandle GetHandle() const { return m_handle; }

    private:
        Transform m_transform{};                                                // following unitys footsteps and not making it a component
        std::unordered_map<TypeId, std::unique_ptr<Component> > m_components{}; // this approach has a downside, you can only have 1 component per type but you eliminate RTTI and you get O(1) lookup :p
        GameObjectHandle m_handle{INVALID_HANDLE};
    };
}
