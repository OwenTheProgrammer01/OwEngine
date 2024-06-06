#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameActor.h"

dae::RenderComponent::RenderComponent(GameActor* pOwner)
	: BaseComponent(pOwner), m_pTexture{ nullptr }
{}

void dae::RenderComponent::Update() {}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
	{
		auto& worldPos{ GetOwner()->GetWorldPosition() };
		Renderer::GetInstance().RenderTexture(*m_pTexture, worldPos.x, worldPos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}