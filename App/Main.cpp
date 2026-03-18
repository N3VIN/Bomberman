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
#include "Components/HealthComponent.h"
#include "Components/LivesDisplayComponent.h"
#include "../Core/Input/InputManager.h"
#include "../Core/Input/Gamepad.h"
#include "Commands/MoveCommand.h"
#include "Commands/DieCommand.h"

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

    constexpr int startingLives = 3;
    const auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

    // player 1
    auto player1 = std::make_unique<dae::GameObject>();
    player1->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    player1->SetLocalPosition(glm::vec2(300, 300));
    auto *p1Health = player1->AddComponent<dae::HealthComponent>(startingLives);
    auto *p1 = player1.get();
    scene.Add(std::move(player1));

    // player 1 lives display
    auto livesDisplay1 = std::make_unique<dae::GameObject>();
    livesDisplay1->SetLocalPosition(glm::vec2(10, 50));
    auto *livesText1 = livesDisplay1->AddComponent<dae::TextComponent>();
    livesText1->SetFont(smallFont);
    livesText1->SetColor({255, 255, 255, 255});
    auto *livesComp1 = livesDisplay1->AddComponent<dae::LivesDisplayComponent>(startingLives);
    p1Health->AddObserver(livesComp1);
    scene.Add(std::move(livesDisplay1));

    // player 2
    auto player2 = std::make_unique<dae::GameObject>();
    player2->AddComponent<dae::RenderComponent>()->SetTexture("bomberman.png");
    player2->SetLocalPosition(glm::vec2(500, 300));
    auto *p2Health = player2->AddComponent<dae::HealthComponent>(startingLives);
    auto *p2 = player2.get();
    scene.Add(std::move(player2));

    // player 2 lives display
    auto livesDisplay2 = std::make_unique<dae::GameObject>();
    livesDisplay2->SetLocalPosition(glm::vec2(10, 80));
    auto *livesText2 = livesDisplay2->AddComponent<dae::TextComponent>();
    livesText2->SetFont(smallFont);
    livesText2->SetColor({255, 200, 100, 255});
    auto *livesComp2 = livesDisplay2->AddComponent<dae::LivesDisplayComponent>(startingLives);
    p2Health->AddObserver(livesComp2);
    scene.Add(std::move(livesDisplay2));

    auto &input = dae::InputManager::GetInstance();
    constexpr float speed1 = 100.f;
    constexpr float speed2 = 200.f;

    // player 1 WASD, C to die
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{0, -1}, speed1));
    input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{0, 1}, speed1));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{-1, 0}, speed1));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec2{1, 0}, speed1));
    input.BindCommand(SDL_SCANCODE_C, dae::KeyState::Down, std::make_unique<dae::DieCommand>(p1));

    // player 2 DPad on controller 0, B to die
    input.BindCommand(0, dae::Gamepad::Button::DpadUp, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{0, -1}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadDown, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{0, 1}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadLeft, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{-1, 0}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::DpadRight, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec2{1, 0}, speed2));
    input.BindCommand(0, dae::Gamepad::Button::B, dae::KeyState::Down, std::make_unique<dae::DieCommand>(p2));
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
