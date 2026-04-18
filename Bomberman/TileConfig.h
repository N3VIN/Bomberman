#pragma once
#include <SDL3/SDL.h>

namespace dae {
    namespace TileConfig {
        constexpr int TileSize = 16;
        constexpr int LevelColumns = 31;
        constexpr int LevelRows = 13;
        constexpr float Scale = 2.0f;

        constexpr auto BackgroundPath = "Sprites/Background.png";
        constexpr auto TilesetPath = "Sprites/Background.png";

        constexpr SDL_Rect BackgroundSourceRect{0, 0, LevelColumns * TileSize, LevelRows * TileSize};
        constexpr SDL_Rect BrickSourceRect{64, 176, TileSize, TileSize};
        constexpr SDL_Rect ExitSourceRect{16, 176, TileSize, TileSize};
    }
}
