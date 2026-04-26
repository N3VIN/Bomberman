#pragma once
#include "../../Core/Components/Component.h"
#include "../Level/TileType.h"
#include <cstdint>
#include <memory>
#include <glm/glm.hpp>
#include <vector>

namespace dae {
    class Level;

    class LevelGridComponent final : public Component {
    public:
        LevelGridComponent(GameObject *parent, std::unique_ptr<Level> level);
        ~LevelGridComponent() override = default;

        [[nodiscard]] bool IsWalkable(glm::ivec2 cell) const;
        void SetWall(glm::ivec2 cell, bool isWall);
        [[nodiscard]] glm::vec2 CellToWorld(glm::ivec2 cell) const;

        [[nodiscard]] float GetCellSize() const;
        [[nodiscard]] glm::ivec2 GetDimensions() const;
        [[nodiscard]] glm::vec2 GetOrigin() const;
        [[nodiscard]] TileType GetTile(int column, int row) const;

    private:
        [[nodiscard]] bool InBounds(glm::ivec2 cell) const;
        [[nodiscard]] size_t Index(glm::ivec2 cell) const;

        std::unique_ptr<Level> m_level;
        std::vector<uint8_t> m_walls{};
    };
}
