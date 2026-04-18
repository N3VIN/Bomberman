#pragma once
#include <vector>
#include <glm/vec2.hpp>

namespace dae {
    class Level;
    class Scene;
    class LevelGridComponent;

    struct LevelSetupResult {
        std::vector<glm::ivec2> playerSpawnPositions{};
        LevelGridComponent *levelGridComponent{};
    };

    LevelSetupResult SetupLevel(const Level &level, Scene &scene);
}
