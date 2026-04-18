#include "GridMovementComponent.h"
#include "LevelGridComponent.h"
#include "../../Core/SceneGraph/GameObject.h"

namespace dae {
    GridMovementComponent::GridMovementComponent(GameObject *parent, LevelGridComponent *level, glm::ivec2 startCell, float cellsPerSecond)
        : Component(parent)
      , m_level(level)
      , m_cell(startCell)
      , m_cellsPerSecond(cellsPerSecond) {
        ApplyVisualPosition();
    }

    void GridMovementComponent::SetDesiredDirection(glm::ivec2 direction) {
        m_queuedDir = direction;
    }

    void GridMovementComponent::Update(float deltaTime) {
        if (!IsMoving()) {
            TryStartMoveInQueuedDir();
        }

        if (IsMoving()) {
            m_progress += m_cellsPerSecond * deltaTime;
            while (m_progress >= 1.f) {
                m_cell += m_activeDir;
                m_progress -= 1.f;

                if (!TryStartMoveInQueuedDir()) {
                    m_activeDir = {0, 0};
                    m_progress = 0.f;
                    break;
                }
            }
        }

        ApplyVisualPosition();
        m_queuedDir = {0, 0};
    }

    bool GridMovementComponent::TryStartMoveInQueuedDir() {
        if (m_queuedDir == glm::ivec2{0, 0}) {
            return false;
        }

        if (!m_level->IsWalkable(m_cell + m_queuedDir)) {
            return false;
        }

        m_activeDir = m_queuedDir;
        return true;
    }

    void GridMovementComponent::ApplyVisualPosition() const {
        const glm::vec2 base = m_level->CellToWorld(m_cell);
        const glm::vec2 offset = glm::vec2(m_activeDir) * m_level->GetCellSize() * m_progress;
        GetParent()->SetLocalPosition(base + offset);
    }
}
