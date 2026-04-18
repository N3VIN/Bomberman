#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include "../Patterns/Singleton.h"
#include "Level.h"

namespace dae {
    class LevelManager final : public Singleton<LevelManager> {
    public:
        void Init(const std::filesystem::path &dataPath);
        Level *LoadLevel(const std::string &file);

    private:
        friend class Singleton<LevelManager>;
        LevelManager() = default;

        std::filesystem::path m_dataPath{};
        std::map<std::string, std::unique_ptr<Level>> m_loadedLevels{};
    };
}
