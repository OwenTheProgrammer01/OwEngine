#pragma once
#include <memory>
#include <string>

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> pTexture) { m_pTexture = std::move(pTexture); }

		RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}
