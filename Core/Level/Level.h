#pragma once
#include <filesystem>
#include <vector>
#include <glm/vec2.hpp>

namespace dae {
    class Level final {
    public:
        explicit Level(const std::filesystem::path &path);
        ~Level() = default;

        Level(const Level &) = delete;
        Level(Level &&) = delete;
        Level &operator=(const Level &) = delete;
        Level &operator=(Level &&) = delete;

        [[nodiscard]] int GetColumns() const {
            return m_columns;
        }

        [[nodiscard]] int GetRows() const {
            return m_rows;
        }

        [[nodiscard]] float GetCellSize() const {
            return m_cellSize;
        }

        [[nodiscard]] glm::vec2 GetOrigin() const {
            return m_origin;
        }

        [[nodiscard]] char GetTile(int column, int row) const;

    private:
        int m_columns{};
        int m_rows{};
        float m_cellSize{};
        glm::vec2 m_origin{};
        std::vector<char> m_tiles{};
    };
}

