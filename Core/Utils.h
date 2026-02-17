#pragma once

namespace dae::utils {
    constexpr float TICKS_PER_SECOND{60.f};

    struct Time final {
        inline static float deltaTime{};
        inline static float fixedDeltaTime{1.f / TICKS_PER_SECOND};
    };
}
