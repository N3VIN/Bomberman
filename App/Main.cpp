#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include <filesystem>

#include "Components/RenderComponent.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/CacheBenchmarkComponent.h"
#include "../Core/Input/InputManager.h"
#include "../Core/Input/Gamepad.h"
#include "Commands/MoveCommand.h"

namespace fs = std::filesystem;

static void load() {
    auto &scene = dae::SceneManager::GetInstance().CreateScene();

    auto go = std::make_unique<dae::GameObject>();
    auto *bg = go->AddComponent<dae::RenderComponent>();
    bg->SetTexture("background.png");
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::RenderComponent>()->SetTexture("logo.png");
    go->SetLocalPosition(glm::vec2(358, 180));
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto *textComp = go->AddComponent<dae::TextComponent>();
    textComp->SetFont(font);
    textComp->SetText("Programming 4 Assignment");
    textComp->SetColor({255, 255, 0, 255});
    go->SetLocalPosition(glm::vec2(292, 20));
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    auto *fpsText = go->AddComponent<dae::TextComponent>();
    fpsText->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
    fpsText->SetColor({0, 255, 0, 255});
    go->AddComponent<dae::FPSComponent>();
    go->SetLocalPosition(glm::vec2(10, 10));
    scene.Add(std::move(go));

    //

    // auto centerPivot = std::make_unique<dae::GameObject>();
    // centerPivot->SetLocalPosition(glm::vec2(256, 288));
    // auto *centerPtr = centerPivot.get();
    // scene.Add(std::move(centerPivot));
    //
    // auto bombermanCW = std::make_unique<dae::GameObject>();
    // bombermanCW->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    // auto *rotatorCW = bombermanCW->AddComponent<dae::RotatorComponent>();
    // rotatorCW->SetRadius(100.f);
    // rotatorCW->SetSpeed(2.f, true);
    // auto *bombermanCWPtr = bombermanCW.get();
    // bombermanCW->SetParent(centerPtr, false);
    // scene.Add(std::move(bombermanCW));
    //
    // auto bombermanCCW = std::make_unique<dae::GameObject>();
    // bombermanCCW->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    // auto *rotatorCCW = bombermanCCW->AddComponent<dae::RotatorComponent>();
    // rotatorCCW->SetRadius(50.f);
    // rotatorCCW->SetSpeed(2.f, false);
    // bombermanCCW->SetParent(bombermanCWPtr, false);
    // scene.Add(std::move(bombermanCCW));

    // go = std::make_unique<dae::GameObject>();
    // go->AddComponent<dae::CacheBenchmarkComponent>();
    // scene.Add(std::move(go));

    auto player1 = std::make_unique<dae::GameObject>();
    player1->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    player1->SetLocalPosition(glm::vec2(300, 300));
    auto *p1 = player1.get();
    scene.Add(std::move(player1));

    auto player2 = std::make_unique<dae::GameObject>();
    player2->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    player2->SetLocalPosition(glm::vec2(500, 300));
    auto *p2 = player2.get();
    scene.Add(std::move(player2));

    auto &input = dae::InputManager::GetInstance();
    constexpr float speed1 = 100.f;
    constexpr float speed2 = 200.f;

    // Player 1 — WASD
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{0, -1}, speed1));
    input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{0, 1}, speed1));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{-1, 0}, speed1));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{1, 0}, speed1));

    // Player 2 — DPad on controller 0
    input.BindCommand(0, dae::Gamepad::Button::DpadUp, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{0, -1}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadDown, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{0, 1}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadLeft, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{-1, 0}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadRight, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{1, 0}, speed2));
}

int main(int, char *[]) {
#if __EMSCRIPTEN__
    fs::path data_location = "";
#else
    fs::path data_location = "./Data/";
    if (!fs::exists(data_location))
        data_location = "../Data/";
#endif
    dae::Minigin engine(data_location);
    engine.Run(load);
    return 0;
}
