#include "Level.h"
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace dae {
    TileType ParseTile(char tile) {
        switch (tile) {
            case '#':
                return TileType::Wall;
            case 'B':
                return TileType::Brick;
            case 'E':
                return TileType::Exit;
            case '1':
                return TileType::Player1Spawn;
            case '2':
                return TileType::Player2Spawn;
            default:
                return TileType::Empty;
        }
    }

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
            for (const std::string rowString = row.get<std::string>(); const char c: rowString) {
                m_tiles.push_back(ParseTile(c));
            }
        }

        if (m_tiles.size() != expectedSize) {
            throw std::runtime_error("Level tile count does not match grid dimensions");
        }
    }

    TileType Level::GetTile(int column, int row) const {
        if (column < 0 || column >= m_columns || row < 0 || row >= m_rows) {
            return TileType::Empty;
        }

        return m_tiles[static_cast<size_t>(row) * static_cast<size_t>(m_columns) + static_cast<size_t>(column)];
    }
}
