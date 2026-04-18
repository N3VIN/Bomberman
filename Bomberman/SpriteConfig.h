#pragma once
#include <SDL3/SDL.h>

namespace dae {
    namespace SpriteConfig {
        constexpr int TileSize = 16;
        constexpr float Scale = 2.0f;

        constexpr auto BackgroundPath = "Sprites/Background.png";
        constexpr auto TilesetPath = "Sprites/Background.png";

        constexpr SDL_Rect BrickSourceRect{64, 176, TileSize, TileSize};
        constexpr SDL_Rect ExitSourceRect{16, 176, TileSize, TileSize};
    }
}
