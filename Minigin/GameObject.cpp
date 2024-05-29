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
	if (IsChild(pParent) || pParent == this || m_pParent == pParent)
		return;
	if (pParent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPos)
		{
			SetLocalPosition(GetWorldPosition() - pParent->GetWorldPosition());
			SetPosDirty();
		}
	}

	if (m_pParent)
		m_pParent->RemoveChild(this);
	m_pParent = pParent;
	if (m_pParent) 
		m_pParent->AddChild(this);
}

dae::GameActor* dae::GameActor::GetChild(size_t idx)
{
	assert(idx < GetChildCount());
	return m_pChildren[idx];
}

void dae::GameActor::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos.SetPosition(pos.x, pos.y, pos.z);
	SetPosDirty();
}

void dae::GameActor::SetWorldPosition(float x, float y)
{
	if (!m_pParent)
		m_LocalPos.SetPosition(x, y, 0);
	SetPosDirty();
}

const glm::vec3& dae::GameActor::GetWorldPosition()
{
	if (m_PosIsDirty)
		UpdateWorldPosition();
	return m_WorldPos;
}

void dae::GameActor::SetPosDirty()
{
	m_PosIsDirty = true;

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

void dae::GameActor::UpdateWorldPosition()
{
	if (m_PosIsDirty)
	{
		if (m_pParent == nullptr)
			m_WorldPos = m_LocalPos.GetPosition();
		else
			m_WorldPos = m_pParent->GetWorldPosition() + m_LocalPos.GetPosition();
	}
	m_PosIsDirty = false;
}

void dae::GameActor::AddChild(GameActor* pChild)
{
	m_pChildren.emplace_back(pChild);
}

void dae::GameActor::RemoveChild(GameActor* pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it != m_pChildren.end())
		m_pChildren.erase(it);
}

bool dae::GameActor::IsChild(GameActor* pOwner) const
{
	return std::find(m_pChildren.begin(), m_pChildren.end(), pOwner) != end(m_pChildren);
}
