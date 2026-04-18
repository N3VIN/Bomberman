#pragma once
#include "../../Core/Components/Component.h"
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace dae {
    class Level;

    class LevelGridComponent final : public Component {
    public:
        LevelGridComponent(GameObject *parent, const Level &level);

        [[nodiscard]] bool IsWalkable(glm::ivec2 cell) const;
        void SetWall(glm::ivec2 cell, bool isWall);
        [[nodiscard]] glm::vec2 CellToWorld(glm::ivec2 cell) const;

        [[nodiscard]] float GetCellSize() const;
        [[nodiscard]] glm::ivec2 GetDimensions() const;
        [[nodiscard]] glm::vec2 GetOrigin() const;

    private:
        [[nodiscard]] bool InBounds(glm::ivec2 cell) const;
        [[nodiscard]] size_t Index(glm::ivec2 cell) const;

        const Level *m_level{};
        std::vector<uint8_t> m_walls{};
    };
}
