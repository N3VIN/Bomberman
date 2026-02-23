#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "Components/Component.h"

namespace dae {
    class Texture2D;

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
        T *AddComponent() {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
            auto &component = m_components.emplace_back(std::make_unique<T>(this));
            return static_cast<T *>(component.get());
        }

        template<typename T>
        T *GetComponent() const {
            for (const auto &component: m_components) {
                if (auto *ptr = dynamic_cast<T *>(component.get())) {
                    return ptr;
                }
            }

            return nullptr;
        }

        template<typename T>
        bool HasComponent() const {
            for (const auto &component: m_components) {
                if (dynamic_cast<T *>(component.get())) {
                    return true;
                }
            }

            return false;
        }

        template<typename T>
        void RemoveComponent() {
            for (size_t i = m_components.size(); i-- > 0;) {
                if (dynamic_cast<T *>(m_components[i].get())) {
                    // assuming that the order for the components dont matter
                    std::swap(m_components[i], m_components.back());
                    m_components.pop_back();
                    return;
                }
            }
        }

        // TODO: SendMessage function

        void SetPosition(const glm::vec2 &position);
        [[nodiscard]] glm::vec2 GetPosition() const;

    private:
        Transform m_transform{}; // following unitys footsteps and not making it a component
        std::vector<std::unique_ptr<Component> > m_components{};
    };
}
