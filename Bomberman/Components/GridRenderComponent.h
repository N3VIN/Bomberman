#pragma once
#include <SDL3/SDL.h>
#include "../../Core/Components/Component.h"

namespace dae {
    class RenderComponent;

    class GridRenderComponent final : public Component {
    public:
        GridRenderComponent(GameObject *parent, const SDL_Rect &backgroundSourceRect);

    private:
        RenderComponent *m_renderComponent{};
    };
}
