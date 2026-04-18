#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include <filesystem>

#include "../Core/Engine/Engine.h"
#include "../Core/SceneGraph/SceneManager.h"
#include "../Core/SceneGraph/Scene.h"
#include "../Core/SceneGraph/GameObject.h"
#include "../Core/Renderer/ResourceManager.h"
#include "../Core/Input/InputManager.h"
#include "../Core/Components/RenderComponent.h"
#include "../Core/Components/TextComponent.h"
#include "../Core/Components/FPSComponent.h"
#include "../Core/Level/LevelManager.h"
#include "../Core/Level/Level.h"

#include "LevelSetup.h"
#include "TileConfig.h"
#include "Components/LevelGridComponent.h"
#include "Components/GridMovementComponent.h"
#include "Commands/GridMoveCommand.h"

namespace fs = std::filesystem;

static void load() {
    auto &scene = dae::SceneManager::GetInstance().CreateScene();

    auto fpsGo = std::make_unique<dae::GameObject>();
    auto *fpsText = fpsGo->AddComponent<dae::TextComponent>();
    fpsText->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
    fpsText->SetColor({0, 255, 0, 255});
    fpsGo->AddComponent<dae::FPSComponent>();
    fpsGo->SetLocalPosition(glm::vec2(10, 10));
    scene.Add(std::move(fpsGo));

    auto *level = dae::LevelManager::GetInstance().LoadLevel("Levels/level1.json");
    const auto setup = dae::SetupLevel(*level, scene);
    auto *levelGrid = setup.levelGridComponent;

    if (setup.playerSpawnPositions.empty()) {
        return;
    }

    auto player = std::make_unique<dae::GameObject>();
    auto *playerRender = player->AddComponent<dae::RenderComponent>();
    playerRender->SetTexture("bomberman.png");
    playerRender->SetScale(dae::TileConfig::Scale);
    player->AddComponent<dae::GridMovementComponent>(levelGrid, setup.playerSpawnPositions[0], 4.f);
    auto *playerPtr = player.get();
    scene.Add(std::move(player));

    auto &input = dae::InputManager::GetInstance();

    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::GridMoveCommand>(playerPtr, glm::ivec2{0, -1}));
    input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::GridMoveCommand>(playerPtr, glm::ivec2{0, 1}));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::GridMoveCommand>(playerPtr, glm::ivec2{-1, 0}));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::GridMoveCommand>(playerPtr, glm::ivec2{1, 0}));
}

int main(int, char *[]) {
#if __EMSCRIPTEN__
    fs::path data_location = "";
#else
    fs::path data_location = "./Data/";
    if (!fs::exists(data_location))
        data_location = "../Data/";
#endif
    dae::Engine engine(data_location);
    engine.Run(load);
    return 0;
}
