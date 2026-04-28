#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "../Core/Engine/Engine.h"
#include "../Core/SceneGraph/SceneManager.h"

#include "Level/BuildLevelScene.h"

namespace fs = std::filesystem;

static void load() {
    auto &levelScene = dae::BuildLevelScene("Levels/level1.json");
    dae::SceneManager::GetInstance().SetActiveScene(levelScene);
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
