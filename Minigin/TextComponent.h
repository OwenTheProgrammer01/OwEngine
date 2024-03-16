#pragma once
#include <string>
#include <memory>

#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class Font;
	class RenderComponent;
	class TextComponent final : public BaseComponent
	{
	public:
		void Update() override;

		void SetText(const std::string& text);

		TextComponent(GameObject* pOwner, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;

		std::shared_ptr<Font> m_pFont;
		RenderComponent* m_pRenderComponent;
	};
}
