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
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto go = std::make_unique<dae::GameObject>();
    auto* bg = go->AddComponent<dae::RenderComponent>();
    bg->SetTexture("background.png");
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
    go->AddComponent<dae::RenderComponent>()->SetTexture("logo.png");
	go->SetPosition(glm::vec2(358, 180));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto* textComp = go->AddComponent<dae::TextComponent>();
	textComp->SetFont(font);
	textComp->SetText("Programming 4 Assignment");
	textComp->SetColor({255, 255, 0, 255});
	go->SetPosition(glm::vec2(292, 20));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto* fpsText = go->AddComponent<dae::TextComponent>();
	fpsText->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	fpsText->SetText("0 FPS"); // TODO: try to find a way to avoid this.
	fpsText->SetColor({0, 255, 0, 255});
	go->AddComponent<dae::FPSComponent>();
	go->SetPosition(glm::vec2(10, 10));
	scene.Add(std::move(go));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
