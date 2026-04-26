#include "LevelGridComponent.h"
#include "../Level/Level.h"

namespace dae {
    LevelGridComponent::LevelGridComponent(GameObject *parent, std::unique_ptr<Level> level)
        : Component(parent)
      , m_level(std::move(level))
      , m_walls(static_cast<size_t>(m_level->GetColumns()) * static_cast<size_t>(m_level->GetRows()), 0) {}

    bool LevelGridComponent::IsWalkable(glm::ivec2 cell) const {
        if (!InBounds(cell)) {
            return false;
        }

        return m_walls[Index(cell)] == 0;
    }

    void LevelGridComponent::SetWall(glm::ivec2 cell, bool isWall) {
        if (!InBounds(cell)) {
            return;
        }

        m_walls[Index(cell)] = isWall ? 1 : 0;
    }

    glm::vec2 LevelGridComponent::CellToWorld(glm::ivec2 cell) const {
        return m_level->GetOrigin() + glm::vec2(cell) * m_level->GetCellSize();
    }

    float LevelGridComponent::GetCellSize() const {
        return m_level->GetCellSize();
    }

    glm::ivec2 LevelGridComponent::GetDimensions() const {
        return {m_level->GetColumns(), m_level->GetRows()};
    }

    glm::vec2 LevelGridComponent::GetOrigin() const {
        return m_level->GetOrigin();
    }

    TileType LevelGridComponent::GetTile(int column, int row) const {
        return m_level->GetTile(column, row);
    }

    bool LevelGridComponent::InBounds(glm::ivec2 cell) const {
        return cell.x >= 0 && cell.x < m_level->GetColumns() && cell.y >= 0 && cell.y < m_level->GetRows();
    }

    size_t LevelGridComponent::Index(glm::ivec2 cell) const {
        return static_cast<size_t>(cell.y) * static_cast<size_t>(m_level->GetColumns()) + static_cast<size_t>(cell.x);
    }
}
