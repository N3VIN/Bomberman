#pragma once

namespace dae {
    struct Time final {
        static constexpr float TICKS_PER_SECOND{60.f};
        static constexpr int MS_PER_FRAME = 16; // 60fps

        inline static float deltaTime{};
        inline static float fixedDeltaTime{1.f / TICKS_PER_SECOND};
    };
}
