#pragma once
#include <SDL3/SDL.h>
#include <array>
#include <optional>
#include <string>

#include "../SpriteConfig.h"
#include "../Components/LevelGridComponent.h"
#include "../Components/GridRenderComponent.h"
#include "../Components/GridMovementComponent.h"
#include "../Commands/GridMoveCommand.h"

#include "Level.h"
#include "../../Core/SceneGraph/Scene.h"
#include "../../Core/SceneGraph/SceneManager.h"
#include "../../Core/SceneGraph/GameObject.h"
#include "../../Core/Components/RenderComponent.h"
#include "../../Core/Components/TextComponent.h"
#include "../../Core/Components/FPSComponent.h"
#include "../../Core/Renderer/ResourceManager.h"
#include "../../Core/Input/InputManager.h"

namespace dae {
    // free function to avoid inheritance for scene
    inline Scene &BuildLevelScene(const std::string &jsonRelativePath) {
        auto level = std::make_unique<Level>(ResourceManager::GetInstance().GetDataPath() / jsonRelativePath);
        auto &scene = SceneManager::GetInstance().CreateScene();

        auto levelGameObject = std::make_unique<GameObject>();
        levelGameObject->SetLocalPosition(level->GetOrigin());

        const SDL_Rect backgroundSourceRect{
            0, 0,
            level->GetColumns() * SpriteConfig::TileSize,
            level->GetRows() * SpriteConfig::TileSize
        };

        levelGameObject->AddComponent<GridRenderComponent>(backgroundSourceRect);

        auto *levelGridComponent = levelGameObject->AddComponent<LevelGridComponent>(std::move(level));

        std::array<glm::ivec2, 2> playerSpawnPositions{};

        const auto spawnTile = [&scene, levelGridComponent](glm::ivec2 cell, const SDL_Rect &srcRect) {
            auto tile = std::make_unique<GameObject>();
            tile->SetLocalPosition(levelGridComponent->CellToWorld(cell));
            auto *renderComponent = tile->AddComponent<RenderComponent>();
            renderComponent->SetTexture(SpriteConfig::TilesetPath);
            renderComponent->SetSourceRect(srcRect);
            renderComponent->SetScale(SpriteConfig::Scale);
            scene.Add(std::move(tile));
        };

        const glm::ivec2 dims = levelGridComponent->GetDimensions();
        for (int column = 0; column < dims.x; ++column) {
            for (int row = 0; row < dims.y; ++row) {
                const glm::ivec2 cell{column, row};
                switch (levelGridComponent->GetTile(column, row)) {
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
                        playerSpawnPositions[0] = cell;
                        break;
                    case TileType::Player2Spawn:
                        playerSpawnPositions[1] = cell;
                        break;
                    case TileType::Empty:
                        break;
                }
            }
        }

        scene.Add(std::move(levelGameObject));

        auto fpsGo = std::make_unique<GameObject>();
        auto *fpsText = fpsGo->AddComponent<TextComponent>();
        fpsText->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
        fpsText->SetColor({0, 255, 0, 255});
        fpsGo->AddComponent<FPSComponent>();
        fpsGo->SetLocalPosition(glm::vec2(10, 10));
        scene.Add(std::move(fpsGo));

        auto player = std::make_unique<GameObject>();
        auto *playerRender = player->AddComponent<RenderComponent>();
        playerRender->SetTexture("bomberman.png");
        playerRender->SetScale(SpriteConfig::Scale);
        player->AddComponent<GridMovementComponent>(levelGridComponent, playerSpawnPositions[0], 4.f);
        auto *playerPtr = player.get();
        scene.Add(std::move(player));

        auto &input = InputManager::GetInstance();
        input.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<GridMoveCommand>(playerPtr, glm::ivec2{0, -1}));
        input.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<GridMoveCommand>(playerPtr, glm::ivec2{0, 1}));
        input.BindCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_unique<GridMoveCommand>(playerPtr, glm::ivec2{-1, 0}));
        input.BindCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_unique<GridMoveCommand>(playerPtr, glm::ivec2{1, 0}));

        return scene;
    }
}
