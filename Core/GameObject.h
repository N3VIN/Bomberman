#pragma once
#include <string>
#include <memory>
#include "Transform.h"

namespace dae {
    class Texture2D;
    class Component;

    class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject();
        GameObject(const GameObject &other) = delete;
        GameObject(GameObject &&other) = delete;
        GameObject &operator=(const GameObject &other) = delete;
        GameObject &operator=(GameObject &&other) = delete;

        virtual void Update();
        virtual void Render() const;

        template<typename T, typename... Args>
        T *AddComponent(Args &&... args);

        template<typename T>
        T *GetComponent() const;

        template<typename T>
        bool HasComponent() const;

        template<typename T>
        void RemoveComponent();

        // TODO: SendMessage function

        void SetTexture(const std::string &filename);
        void SetPosition(float x, float y);

    private:
        Transform m_transform{};
        std::vector<std::unique_ptr<Component> > m_components{};
        std::shared_ptr<Texture2D> m_texture{};
    };
}
