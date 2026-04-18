#include "LevelSetup.h"
#include "../SpriteConfig.h"
#include "../Components/LevelGridComponent.h"
#include "../Components/GridRenderComponent.h"
#include "../../Core/Level/Level.h"
#include "../../Core/SceneGraph/Scene.h"
#include "../../Core/SceneGraph/GameObject.h"
#include "../../Core/Components/RenderComponent.h"

namespace dae {
    LevelSetupResult SetupLevel(const Level &level, Scene &scene) {
        LevelSetupResult result{};
        auto levelGameObject = std::make_unique<GameObject>();
        levelGameObject->SetLocalPosition(level.GetOrigin());
        auto *levelGridComponent = levelGameObject->AddComponent<LevelGridComponent>(level);
        const SDL_Rect backgroundSourceRect{
            0, 0,
            level.GetColumns() * SpriteConfig::TileSize,
            level.GetRows() * SpriteConfig::TileSize
        };

        levelGameObject->AddComponent<GridRenderComponent>(backgroundSourceRect);
        result.levelGridComponent = levelGridComponent;

        const auto spawnTile = [&scene, &level](glm::ivec2 cell, const SDL_Rect &srcRect) {
            auto tile = std::make_unique<GameObject>();
            tile->SetLocalPosition(level.GetOrigin() + glm::vec2(cell) * level.GetCellSize());
            auto *renderComponent = tile->AddComponent<RenderComponent>();
            renderComponent->SetTexture(SpriteConfig::TilesetPath);
            renderComponent->SetSourceRect(srcRect);
            renderComponent->SetScale(SpriteConfig::Scale);
            scene.Add(std::move(tile));
        };

        for (int column = 0; column < level.GetColumns(); ++column) {
            for (int row = 0; row < level.GetRows(); ++row) {
                const glm::ivec2 cell{column, row};
                switch (level.GetTile(column, row)) {
                    case TileType::Wall:
                        levelGridComponent->SetWall(cell, true);
                        break;
                    case TileType::Brick:
                        spawnTile(cell, SpriteConfig::BrickSourceRect);
                        break;
                    case TileType::Exit:
                        spawnTile(cell, SpriteConfig::ExitSourceRect);
                        break;
                    case TileType::Player1Spawn:
                        break;
                    case TileType::Player2Spawn:
                        result.playerSpawnPositions.push_back(cell);
                        break;
                    case TileType::Empty:
                        break;
                }
            }
        }

        scene.Add(std::move(levelGameObject));
        return result;
    }
}
