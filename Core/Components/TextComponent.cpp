#include <stdexcept>
#include "TextComponent.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae {
    TextComponent::TextComponent(GameObject *owner)
        : Component(owner) {}

    void TextComponent::Update(float /*deltaTime*/) {
        if (m_needsUpdate && m_font) {
            const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
            if (surf == nullptr) {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }

            auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            if (texture == nullptr) {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }

            SDL_DestroySurface(surf);
            m_textTexture = std::make_shared<Texture2D>(texture);
            m_needsUpdate = false;
        }
    }

    void TextComponent::Render() const {
        if (m_textTexture != nullptr) {
            const auto &pos = m_parent->GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    void TextComponent::SetText(const std::string &text) {
        m_text = text;
        m_needsUpdate = true;
    }

    void TextComponent::SetFont(std::shared_ptr<Font> font) {
        m_font = std::move(font);
        m_needsUpdate = true;
    }

    void TextComponent::SetColor(const SDL_Color &color) {
        m_color = color;
        m_needsUpdate = true;
    }
} // dae
