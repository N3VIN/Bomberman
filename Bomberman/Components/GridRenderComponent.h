#pragma once
#include "../../Core/Components/Component.h"

namespace dae {
    class RenderComponent;

    class GridRenderComponent final : public Component {
    public:
        explicit GridRenderComponent(GameObject *parent);

    private:
        RenderComponent *m_renderComponent{};
    };
}
