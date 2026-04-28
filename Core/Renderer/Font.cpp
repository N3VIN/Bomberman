#include "Font.h"

TTF_Font *dae::Font::GetFont() const {
    return m_font;
}

dae::Font::Font(std::string_view fullPath, float size)
    : m_font(nullptr) {
    m_font = TTF_OpenFont(fullPath.data(), size);

    if (m_font == nullptr) {
        throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
    }
}

dae::Font::~Font() {
    TTF_CloseFont(m_font);
}
