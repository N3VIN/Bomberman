#include "LevelManager.h"

namespace dae {
    void LevelManager::Init(const std::filesystem::path &dataPath) {
        m_dataPath = dataPath;
    }

    Level *LevelManager::LoadLevel(const std::string &file) {
        if (const auto it = m_loadedLevels.find(file); it != m_loadedLevels.end()) {
            return it->second.get();
        }

        auto level = std::make_unique<Level>(m_dataPath / file);
        auto *levelPtr = level.get();
        m_loadedLevels.emplace(file, std::move(level));
        return levelPtr;
    }
}
