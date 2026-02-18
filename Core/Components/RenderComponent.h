#pragma once
#include <memory>
#include <string>
#include "Component.h"

namespace dae {
    class Texture2D;
    class GameObject;

    class RenderComponent final : public Component {
    public:
        explicit RenderComponent(GameObject *parent);
        void Update(float deltaTime) override;
        void Render() const override;

        void SetTexture(const std::string &filename);

    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
}

