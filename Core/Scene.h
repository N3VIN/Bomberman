#pragma once
#include <memory>
// #include <string>
#include <vector>
#include <unordered_map>
#include "GameObject.h"

namespace dae {
    class Scene final {
    public:
        GameObjectHandle Add(std::unique_ptr<GameObject> object);
        void Remove(GameObjectHandle handle);
        void Remove(const GameObject* object);
        void RemoveAll();

        [[nodiscard]] GameObject* Get(GameObjectHandle handle) const;

        void Update(float deltaTime);
        void FixedUpdate();
        void Render() const;

        ~Scene() = default;
        Scene(const Scene &other) = delete;
        Scene(Scene &&other) = delete;
        Scene &operator=(const Scene &other) = delete;
        Scene &operator=(Scene &&other) = delete;

    private:
        friend class SceneManager;
        explicit Scene() = default;

        std::vector<std::unique_ptr<GameObject>> m_objects{};
        std::unordered_map<GameObjectHandle, size_t> m_handleToIndex{};
        GameObjectHandle m_nextHandle{0};
    };
}
