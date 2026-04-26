#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "../Patterns/Singleton.h"

namespace dae {
    class Scene;

    class SceneManager final : public Singleton<SceneManager> {
    public:
        Scene &CreateScene();

        void SetActiveScene(Scene &scene);

        [[nodiscard]] Scene *GetActiveScene() const {
            return m_activeScene;
        }

        void Update(float deltaTime);
        void FixedUpdate();
        void Render() const;

    private:
        friend class Singleton<SceneManager>;
        SceneManager() = default;
        std::vector<std::unique_ptr<Scene> > m_scenes{};
        Scene *m_activeScene{};
    };
}
