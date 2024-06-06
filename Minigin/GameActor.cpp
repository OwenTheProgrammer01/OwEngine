#include <string>

#include "GameActor.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"

void dae::GameActor::Update()
{
	for (const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameActor::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameActor::SetParent(GameActor* pParent, bool keepWorldPos)
{
	if (IsChild(pParent) || pParent == this || m_pParent == pParent) return;
	if (pParent == nullptr)	SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPos) SetLocalPosition(GetWorldPosition() - pParent->GetWorldPosition());
		SetPosDirty();
	}
	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = pParent;
	if (m_pParent) m_pParent->AddChild(this);
}

void dae::GameActor::SetWorldPosition(const glm::vec3& worldPos)
{
	if (!m_pParent)	
	{
		SetLocalPosition(worldPos);
	}
	SetPosDirty();
}

void dae::GameActor::SetLocalPosition(const glm::vec3& localPos)
{
	m_Transform.SetLocalPosition(localPos);
	SetPosDirty();
}

void dae::GameActor::SetPosDirty()
{
	m_IsPosDirty = true;

	for (const auto& child : m_pChildren)
	{
		child->SetPosDirty();
	}
}

void dae::GameActor::SetDeleteFlag()
{
	m_DeleteFlag = true;

	for (const auto& child : m_pChildren)
	{
		child->SetDeleteFlag();
	}
}

void dae::GameActor::AddChild(GameActor* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void dae::GameActor::RemoveChild(GameActor* pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it != m_pChildren.end()) m_pChildren.erase(it);
}

bool dae::GameActor::IsChild(GameActor* pOwner) const
{
	return std::find(m_pChildren.begin(), m_pChildren.end(), pOwner) != end(m_pChildren);
}

void dae::GameActor::UpdateWorldPosition()
{
	if (m_IsPosDirty)
	{
		if (m_pParent == nullptr) m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
		else m_Transform.SetWorldPosition(m_pParent->GetWorldPosition() + m_Transform.GetLocalPosition());
	}
	m_IsPosDirty = false;
}