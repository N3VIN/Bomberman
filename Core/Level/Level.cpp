#include "Level.h"
#include <fstream>
#include <stdexcept>
#include <ranges>
#include <nlohmann/json.hpp>

namespace dae {
    Level::Level(const std::filesystem::path &path) {
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error("Level file not found: " + path.string());
        }

        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open level file: " + path.string());
        }

        nlohmann::json json;
        file >> json;

        const auto &grid = json.at("grid");
        m_columns = grid.at("columns").get<int>();
        m_rows = grid.at("rows").get<int>();
        m_cellSize = grid.at("cellSize").get<float>();

        const auto &origin = json.at("origin");
        m_origin.x = origin.at("x").get<float>();
        m_origin.y = origin.at("y").get<float>();

        const auto &tiles = json.at("tiles");
        const size_t expectedSize = static_cast<size_t>(m_columns) * static_cast<size_t>(m_rows);
        m_tiles.reserve(expectedSize);

        for (const auto &row: tiles) {
            const std::string rowString = row.get<std::string>();
            std::ranges::copy(rowString, std::back_inserter(m_tiles));
        }

        if (m_tiles.size() != expectedSize) {
            throw std::runtime_error("Level tile count does not match grid dimensions");
        }
    }

    char Level::GetTile(int column, int row) const {
        if (column < 0 || column >= m_columns || row < 0 || row >= m_rows) {
            return '\0';
        }

        return m_tiles[static_cast<size_t>(row) * static_cast<size_t>(m_columns) + static_cast<size_t>(column)];
    }
}
