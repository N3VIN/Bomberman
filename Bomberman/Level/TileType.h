#pragma once
#include <cstdint>

namespace dae {
    enum class TileType : uint8_t {
        Empty,
        Wall,
        Brick,
        Exit,
        Player1Spawn,
        Player2Spawn
    };
}
