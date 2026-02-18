#pragma once
#include <string>
#include <memory>
#include "Transform.h"

namespace dae {
    class Texture2D;
    class Component;

    class GameObject final {
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

    private:
        Transform m_transform{};
        std::vector<std::unique_ptr<Component> > m_components{};
    };
}
