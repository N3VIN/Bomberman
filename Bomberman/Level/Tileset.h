#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>
#include <nlohmann/json.hpp>

#include "../../Core/Renderer/ResourceManager.h"

namespace dae {
    struct Tileset {
        std::string texturePath;
        int tileSize{};
        glm::ivec2 backgroundCoord{};
        glm::ivec2 brickCoord{};
        glm::ivec2 exitCoord{};
    };

    inline const Tileset &GetTileset() {
        static const Tileset tileset = [] {
            const auto path = ResourceManager::GetInstance().GetDataPath() / "Levels" / "tileset.json";

            std::ifstream file(path);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open tileset file: " + path.string());
            }

            nlohmann::json json;
            file >> json;

            const auto readCoord = [&](const char *key) {
                const auto &node = json.at("tiles").at(key);
                return glm::ivec2{node.at("x").get<int>(), node.at("y").get<int>()};
            };

            Tileset t;
            t.texturePath = json.at("texture").get<std::string>();
            t.tileSize = json.at("tileSize").get<int>();
            t.backgroundCoord = readCoord("background");
            t.brickCoord = readCoord("brick");
            t.exitCoord = readCoord("exit");
            return t;
        }();

        return tileset;
    }
}
