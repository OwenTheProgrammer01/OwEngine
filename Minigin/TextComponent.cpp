#include <stdexcept>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameActor* pOwner, std::shared_ptr<Font> font)
	: BaseComponent(pOwner), m_needsUpdate{ true }, m_text{ " " }, m_pFont{ std::move(font) }, m_pRenderComponent{ pOwner->GetComponent<RenderComponent>() }
{
	assert(m_pRenderComponent);
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;

	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}