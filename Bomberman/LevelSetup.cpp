#include "LevelSetup.h"
#include "TileConfig.h"
#include "Components/LevelGridComponent.h"
#include "Components/GridRenderComponent.h"
#include "../Core/Level/Level.h"
#include "../Core/SceneGraph/Scene.h"
#include "../Core/SceneGraph/GameObject.h"
#include "../Core/Components/RenderComponent.h"

namespace dae {
    LevelSetupResult SetupLevel(const Level &level, Scene &scene) {
        LevelSetupResult result{};

        auto levelGameObject = std::make_unique<GameObject>();
        levelGameObject->SetLocalPosition(level.GetOrigin());
        auto *levelGridComponent = levelGameObject->AddComponent<LevelGridComponent>(level);
        levelGameObject->AddComponent<GridRenderComponent>();
        result.levelGridComponent = levelGridComponent;

        const auto spawnTile = [&scene, &level](glm::ivec2 cell, const SDL_Rect &srcRect) {
            auto tile = std::make_unique<GameObject>();
            tile->SetLocalPosition(level.GetOrigin() + glm::vec2(cell) * level.GetCellSize());
            auto *renderComponent = tile->AddComponent<RenderComponent>();
            renderComponent->SetTexture(TileConfig::TilesetPath);
            renderComponent->SetSourceRect(srcRect);
            renderComponent->SetScale(TileConfig::Scale);
            scene.Add(std::move(tile));
        };

        for (int row = 0; row < level.GetRows(); ++row) {
            for (int column = 0; column < level.GetColumns(); ++column) {
                const glm::ivec2 cell{column, row};
                switch (level.GetTile(column, row)) {
                    case '#':
                        levelGridComponent->SetWall(cell, true);
                        break;
                    case 'B':
                        spawnTile(cell, TileConfig::BrickSourceRect);
                        break;
                    case 'E':
                        spawnTile(cell, TileConfig::ExitSourceRect);
                        break;
                    case '1':
                    case '2':
                        result.playerSpawnPositions.push_back(cell);
                        break;
                    default:
                        break;
                }
            }
        }

        scene.Add(std::move(levelGameObject));
        return result;
    }
}
